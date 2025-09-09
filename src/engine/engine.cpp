#include "engine.h"

#include "physics.h"
#include "collision.h"
#include "../input.h"
#include "../input_handler.h"
#include <utility>

Engine::Engine()
    : window_(nullptr), renderer_(nullptr) {}

Engine::~Engine()
{
    cleanup();
}

bool Engine::init(const char *title, int width, int height)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer(title, width, height, 0, &window_, &renderer_))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    SDL_SetWindowResizable(window_, true);
    // Initialize logical render size baseline and default scaling mode (delegated)
    scaler_.init(window_, renderer_, width, height, entities_);
    // Register scaling controller with input to handle key toggles
    input_handler::setScalingController(&scaler_, renderer_, &entities_);
    return true;
}


void handleSpriteSheetAnimation(Entity &e, unsigned long long frame)
{
    const int frameRowCount = e.getFrameRowCount();
    const int frameColumnCount = e.getFrameColumnCount();
    const int animationDelay = e.getAnimationDelay();

    if (frameColumnCount > 0 && animationDelay > 0 && frame % animationDelay == 0)
    {
        int currentFrameColumn = e.getCurrentFrameColumn();
        int currentFrameRow = e.getCurrentFrameRow();

        if (currentFrameColumn + 1 >= frameColumnCount)
        {
            currentFrameColumn = 0;
            currentFrameRow++;
            if (currentFrameRow >= frameRowCount)
            {
                currentFrameRow = 0;
            }
        }
        else
        {
            currentFrameColumn++;
        }

        e.setCurrentFrameColumn(currentFrameColumn);
        e.setCurrentFrameRow(currentFrameRow);
    }
}

void handleAutoMovingEntityUpdate(Entity &e)
{
    if (e.isControllable() or !e.isMovable() or !e.hasPathVectors())
        return;

    int updatesRemaining = e.getPathVectorUpdatesRemaining();
    if (updatesRemaining <= 0)
    {
        int nextIndex = e.getNextPathVectorIndex();
        const std::vector<Entity::PathVector> &pathVectors = e.getPathVectors();
        const Entity::PathVector &pv = pathVectors[nextIndex];
        e.setVelocityX(pv.vx);
        e.setVelocityY(pv.vy);
        e.setPathVectors(pathVectors); // Refresh to update internal state
        e.setNextPathVectorIndex((nextIndex + 1) % pathVectors.size());
        e.setPathVectorUpdatesRemaining(pv.updates);
    }
    else
    {
        e.setPathVectorUpdatesRemaining(updatesRemaining - 1);
    }
}

void Engine::run()
{
    if (!window_ || !renderer_)
    {
        return;
    }

    bool running = true;
    SDL_Event event;
    unsigned long long tick = 0ULL;
    unsigned long long frame = 0ULL;
    while (running)
    {
        ++tick;
        if (tick % 10000000 == 0)
        {
            frame++;

            // Detect input snapshot for this frame and handle gameplay input
            input::detect();

            // Scaling toggles are handled in input_handler now
            input_handler::handleInput();
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    running = false;
                }
                else if (event.type == SDL_EVENT_MOUSE_WHEEL)
                {
                    scaler_.onMouseWheel(event, window_);
                }
                // Forward discrete events (mouse, keydown) to input module
                input_handler::handleEvent(event);
            }

            // Clear frame
            SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
            SDL_RenderClear(renderer_);

            // Update, animate and render entities
            for (auto &e : entities_)
            {   
                if(e.isDisabled()) continue;
                if (!input_handler::isPaused()) {

                    if(e.isControllable() && e.isReset()) {
                        e.setX(500);
                        e.setY(-100);
                        e.setVelocityX(0);
                        e.setVelocityY(0);
                        e.setReset(false);
                    }

                    handleSpriteSheetAnimation(e, frame);
                    handleAutoMovingEntityUpdate(e);
                    
                    // // Allow custom per-entity updates
                    // e.update();

                    // Apply physics (velocity, acceleration, collisions)
                    std::pair<std::pair<float, float>, std::pair<float, float>> targetVectors = Physics::applyPhysics(e);

                    handle_collision(e, targetVectors.first.first, targetVectors.first.second, targetVectors.second.first, targetVectors.second.second);
                }

                // Source rectangle from spritesheet
                SDL_FRect src{static_cast<float>(e.getCurrentFrameColumn()) * e.getWidth(), e.getCurrentFrameRow() * e.getHeight(), e.getWidth(), e.getHeight()};

                // Destination rectangle on screen
                const float scale = e.getScale();
                SDL_FRect dst{e.getX(), e.getY(), e.getWidth() * scale, e.getHeight() * scale};

                // Draw
                if (SDL_Texture *tex = e.getTexture())
                {
                    SDL_RenderTexture(renderer_, tex, &src, &dst);
                }
            }

            // If paused, draw a translucent overlay with a pause icon
            if (input_handler::isPaused()) {
                int irw = 0, irh = 0;
                SDL_GetRenderOutputSize(renderer_, &irw, &irh);
                const float rw = static_cast<float>(irw);
                const float rh = static_cast<float>(irh);
                SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 160);
                SDL_FRect fade{0.0f, 0.0f, rw, rh};
                SDL_RenderFillRect(renderer_, &fade);
            }

            SDL_RenderPresent(renderer_);
        }
    }
}

void Engine::cleanup()
{
    for (auto &e : entities_)
    {
        if (SDL_Texture *tex = e.getTexture())
        {
            SDL_DestroyTexture(tex);
        }
    }

    if (renderer_)
    {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
    if (window_)
    {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    SDL_Quit();
}

Entity *Engine::addEntity(const Entity &entity)
{
    entities_.push_back(entity);
    return &entities_.back();
}
