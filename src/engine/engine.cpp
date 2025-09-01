#include "engine.h"

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

            // Allow custom per-entity updates
            e.update();

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
