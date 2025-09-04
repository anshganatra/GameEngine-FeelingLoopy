#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <unordered_set>
#include <string>
#include "engine/entity.h"

// Only set velocity here; Physics/Engine integrates and resolves collisions.

static bool wasSpacePressed = false;
static bool wasEnterPressed = false;
static bool wasEscapePressed = false;

//static std::unordered_set<size_t> directionsLogged;
static std::unordered_set<std::string> directionsLogged;

// Configurable speeds (units per second)
static float gMoveSpeed = 300.0f;   // horizontal move speed (px/s)
static float gJumpImpulse = 800.0f; // initial jump velocity upward (px/s)

// Pointer to the currently controlled entity (set by the game code)
static Entity* gControlledEntity = nullptr;

void setControlledEntity(Entity* e) { gControlledEntity = e; }
void setMoveSpeed(float units_per_second) { gMoveSpeed = units_per_second; }
void setJumpImpulse(float units_per_second) { gJumpImpulse = units_per_second; }

// Main Input Handling Function
void handleInput()
{
    const bool *state = SDL_GetKeyboardState(NULL);

    // Note: Engine owns SDL_PollEvent and forwards discrete events via handleEvent.

    // If Escape is pressed, then pause the game (placeholder)
    bool isEscapePressed = state[SDL_SCANCODE_ESCAPE];
    if (isEscapePressed && !wasEscapePressed)
    {
        // TODO: toggle pause state here
        wasEscapePressed = isEscapePressed;
    }

    // Movement Controls (WASD)
    const bool up = state[SDL_SCANCODE_W];
    const bool down = state[SDL_SCANCODE_S];
    const bool left = state[SDL_SCANCODE_A];
    const bool right = state[SDL_SCANCODE_D];

    if (up)   directionsLogged.insert(std::string("W")); else directionsLogged.erase(std::string("W"));
    if (down) directionsLogged.insert(std::string("S")); else directionsLogged.erase(std::string("S"));
    if (left) directionsLogged.insert(std::string("A")); else directionsLogged.erase(std::string("A"));
    if (right)directionsLogged.insert(std::string("D")); else directionsLogged.erase(std::string("D"));

    if (gControlledEntity) {
        // Horizontal: set desired velocity directly so Physics can integrate position
        float vx = 0.0f;
        if (left && !right)  vx = -gMoveSpeed;
        if (right && !left)  vx =  gMoveSpeed;
        gControlledEntity->setVelocityX(vx);

        // Vertical: if gravity is disabled (e.g., top-down), use WASD for Y.
        // If gravity is enabled (platformer), don't override vy continuously;
        // only apply jump impulse on Space press.
        if (!gControlledEntity->getisAffectedByGravity()) {
            float vy = 0.0f;
            if (up && !down)    vy = -gMoveSpeed;
            if (down && !up)    vy =  gMoveSpeed;
            gControlledEntity->setVelocityY(vy);
        }
    }

    // Jump (Space): give an instantaneous upward velocity if gravity is on
    bool isSpacePressed = state[SDL_SCANCODE_SPACE];
    if (gControlledEntity && isSpacePressed && !wasSpacePressed) {
        if (gControlledEntity->getisAffectedByGravity()) {
            gControlledEntity->setVelocityY(-gJumpImpulse);
        }
        // else: in no-gravity mode, Space can be repurposed if needed
    }
    wasSpacePressed = isSpacePressed;
}

// Handle discrete events (Engine forwards these)
void handleEvent(const SDL_Event& e) {
    if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float mouseX = 0.0f, mouseY = 0.0f;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (e.button.button == SDL_BUTTON_LEFT) {
            SDL_Log("Left Mouse Button Clicked at X: %f, Y: %f", mouseX, mouseY);
        } 
        else if (e.button.button == SDL_BUTTON_RIGHT) {
            SDL_Log("Right Mouse Button Clicked at X: %f, Y: %f", mouseX, mouseY);
        } 
        else if (e.button.button == SDL_BUTTON_MIDDLE) {
            SDL_Log("Middle Mouse Button Clicked at X: %f, Y: %f", mouseX, mouseY);
        }
    }
}
