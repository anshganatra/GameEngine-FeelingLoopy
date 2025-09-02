#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <unordered_set>
#include "engine/entity.h"

// Update only velocity from keyboard input; no collision or position updates.

// No collision or position helpers needed here


static bool wasSpacePressed = false;
static bool wasEnterPressed = false;
static bool wasEscapePressed = false;

//static std::unordered_set<size_t> directionsLogged;
static std::unordered_set<std::string> directionsLogged;

// Pointer to the currently controlled entity (set by the game code)
static Entity* gControlledEntity = nullptr;

// Allow the game to register which entity should be moved by input
void setControlledEntity(Entity* e) {
    gControlledEntity = e;
}

// Main Input Handling Function
void handleInput()
{
    const bool *state = SDL_GetKeyboardState(NULL);

    // Do not poll events here; Engine owns SDL_PollEvent to avoid swallowing mouse clicks

    // If Escape if Pressed, then Pause the Game
    bool isEscapePressed = state[SDL_SCANCODE_ESCAPE];
    if (isEscapePressed && !wasEscapePressed)
    {
        // Code to toggle pause state

        wasEscapePressed = isEscapePressed;
    }

    // Movement Controls (WASD): increment velocity only, no position updates
    // Note: we adjust existing velocity instead of replacing it
    constexpr float speed = 2.0f; // per-input tick impulse

    const bool up = state[SDL_SCANCODE_W];
    const bool down = state[SDL_SCANCODE_S];
    const bool left = state[SDL_SCANCODE_A];
    const bool right = state[SDL_SCANCODE_D];

    if (gControlledEntity) {
        float vx = gControlledEntity->getVelocityX();
        float vy = gControlledEntity->getVelocityY();

        if (up)    { vy -= speed; directionsLogged.insert(std::string("W")); } else { directionsLogged.erase(std::string("W")); }
        if (down)  { vy += speed; directionsLogged.insert(std::string("S")); } else { directionsLogged.erase(std::string("S")); }
        if (left)  { vx -= speed; directionsLogged.insert(std::string("A")); } else { directionsLogged.erase(std::string("A")); }
        if (right) { vx += speed; directionsLogged.insert(std::string("D")); } else { directionsLogged.erase(std::string("D")); }

        gControlledEntity->setVelocityX(vx);
        gControlledEntity->setVelocityY(vy);
    }


    // If Space is Pressed, then Jump
    bool isSpacePressed = state[SDL_SCANCODE_SPACE];
    if (isSpacePressed && !wasSpacePressed) {
        // Code to make the character jump
        
    }
    wasSpacePressed = isSpacePressed;
}

// Handle discrete events
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
