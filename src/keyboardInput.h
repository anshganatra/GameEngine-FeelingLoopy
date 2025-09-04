#pragma once

#include "engine/entity.h"

// Registers which entity should respond to WASD input
void setControlledEntity(Entity* e);

// Configure input-driven movement speeds (units per second)
void setMoveSpeed(float units_per_second);
void setJumpImpulse(float units_per_second);

// Polls input and moves the controlled entity
void handleInput();

// Receives discrete SDL events (e.g., mouse clicks) from the engine
void handleEvent(const SDL_Event& e);
