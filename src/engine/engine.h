#ifndef ENGINE_H
#define ENGINE_H

#include "entity.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <functional>
#include <vector>
#include "../keyboardInput.h"

class Engine
{
private:
    SDL_Window *window_;
    SDL_Renderer *renderer_;
    std::vector<Entity> entities_;

public:
    Engine();
    ~Engine();

    bool init(const char* title, int width, int height);
    void run();
    void cleanup();

    Entity* addEntity(const Entity &entity);

    // Expose renderer for texture creation (read-only access)
    SDL_Renderer* getRenderer() const { return renderer_; }

    // Read-only access to entities for collision checks
    const std::vector<Entity>& getEntities() const { return entities_; }
};

#endif
