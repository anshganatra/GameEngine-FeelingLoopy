#include "engine.h"

#include "physics.h"
#include "collision.h"
#include <utility>

Engine::Engine()
    : window_(nullptr), renderer_(nullptr) {}

Engine::~Engine() {
    cleanup();
}

//TODO add params for the title, height and width of the game window
bool Engine::init(const char* title, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer(title, width, height, 0, &window_, &renderer_)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    return true;
}



void Engine::run() {
    if (!window_ || !renderer_) {
        return;
    }

    bool running = true;
    SDL_Event event;
    unsigned long long tick = 0ULL;

    while (running) {
        // Handle keyboard input (moves controlled entity)
        handleInput();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            // Forward discrete events (mouse, keydown) to input module
            handleEvent(event);
        }

        // Advance global tick used for animation pacing
        ++tick;

        // Clear frame
        SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
        SDL_RenderClear(renderer_);

        // Update, animate and render entities
        for (auto &e : entities_) {
            // Per-entity animation step based on delay
            const int frameRowCount = e.getFrameRowCount();
            const int frameColumnCount = e.getFrameColumnCount();
            const int delay = e.getAnimationDelay();
            const bool isControllable = e.isControllable();


            if (frameColumnCount > 0 && delay > 0 && !isControllable && (tick % static_cast<unsigned long long>(delay) == 0ULL)) {
                int currentFrameColumn = e.getCurrentFrameColumn();
                int currentFrameRow = e.getCurrentFrameRow();

                if (currentFrameColumn + 1 >= frameColumnCount) {
                    currentFrameColumn = 0;
                    currentFrameRow++;
                    if (currentFrameRow >= frameRowCount) {
                        currentFrameRow = 0;
                    }
                }
                else {
                    currentFrameColumn++;
                }

                e.setCurrentFrameColumn(currentFrameColumn);
                e.setCurrentFrameRow(currentFrameRow);
            }

            if(e.isMovable() && !e.isControllable() && (tick % static_cast<unsigned long long>(delay) == 0ULL)) {
                // Auto-move along predefined path on animation ticks
                if (e.hasPath()) {
                    const auto &path = e.getPath();
                    
                    int idx = e.getNextPathIndex();
                    if (idx >= 0 && idx < static_cast<int>(path.size())) {
                        const float tx = path[idx].x;
                        const float ty = path[idx].y;
                        // SDL_Log("Entity (%s) at (%.1f, %.1f) moving towards (%.1f, %.1f)\n", e.getName().c_str(), e.getX(), e.getY(), tx, ty);
                        const float cx = e.getX();
                        const float cy = e.getY();

                        const float dx = tx - cx;
                        const float dy = ty - cy;

                        float vx = e.getVelocityX();
                        float vy = e.getVelocityY();

                        // If no velocity, nothing to do
                        const float absVx = vx < 0 ? -vx : vx;
                        const float absVy = vy < 0 ? -vy : vy;

                        if (absVx == 0.0f && absVy == 0.0f) {
                            // keep path index unchanged
                        } else {
                            // Move using velocity towards target (adjust sign)
                            vx = (dx >= 0.0f ? absVx : -absVx);
                            vy = (dy >= 0.0f ? absVy : -absVy);

                            // If within one step, snap to target and advance
                            if (dx*dx + dy*dy <= vx*vx + vy*vy) {
                                e.setX(tx);
                                e.setY(ty);
                                // Advance to next point
                                const int nextIdx = idx + 1;
                                e.setNextPathIndex(nextIdx < static_cast<int>(path.size()) ? nextIdx : nextIdx % path.size());
                            } else {
                                e.setVelocityX(vx);
                                e.setVelocityY(vy);
                                e.setX(cx + vx);
                                e.setY(cy + vy);
                            }
                        }
                    }
                }
            }
            
            // Allow custom per-entity updates
            e.update();

            // Apply physics (velocity, acceleration, collisions)
            std::pair<std::pair<float,float>, std::pair<float,float>> targetVectors = Physics::applyPhysics(e);
            
            handle_collision(e, targetVectors.first.first, targetVectors.first.second, targetVectors.second.first, targetVectors.second.second);

            // Source rectangle from spritesheet
            SDL_FRect src { static_cast<float>(e.getCurrentFrameColumn()) * e.getWidth(), e.getCurrentFrameRow() * e.getHeight(), e.getWidth(), e.getHeight() };

            // Destination rectangle on screen
            const float scale = e.getScale();
            SDL_FRect dst { e.getX(), e.getY(), e.getWidth() * scale, e.getHeight() * scale };

            // Draw
            if (SDL_Texture *tex = e.getTexture()) {
                SDL_RenderTexture(renderer_, tex, &src, &dst);
            }
        }

        SDL_RenderPresent(renderer_);
    }
}

void Engine::cleanup() {
    for (auto &e : entities_) {
        if (SDL_Texture *tex = e.getTexture()) {
            SDL_DestroyTexture(tex);
        }
    }

    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    SDL_Quit();
}

Entity* Engine::addEntity(const Entity &entity) {
    entities_.push_back(entity);
    return &entities_.back();
}
