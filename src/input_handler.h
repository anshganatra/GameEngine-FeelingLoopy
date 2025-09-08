// Maps input state to gameplay actions
#pragma once

#include <SDL3/SDL.h>
#include "engine/entity.h"
#include "engine/scaling.h"

namespace input_handler {

// Rebindable movement keys per entity
struct KeyMap {
    SDL_Scancode up;
    SDL_Scancode down;
    SDL_Scancode left;
    SDL_Scancode right;
    SDL_Scancode jump;
};

void setControlledEntity(Entity* e);

// Configure keys for a specific entity (overrides defaults)
void setKeyMapFor(Entity* e, const KeyMap& map);
void clearKeyMapFor(Entity* e);

// Set global default mapping used when an entity has no override
void setDefaultKeyMap(const KeyMap& map);

// Performs movement/jump/pause handling based on input::state
void handleInput();

// Pass-through for discrete SDL events (mouse etc.)
void handleEvent(const SDL_Event& e);

// Paused state (toggled with Escape)
bool isPaused();

// Optional: register scaling controller for render-scale toggles
void setScalingController(scaling::Controller* controller, SDL_Renderer* renderer, std::vector<Entity>* entities);

}
