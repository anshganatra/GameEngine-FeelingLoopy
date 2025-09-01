#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <unordered_set>
#include "engine/entity.h"

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

    // Movement Controls (WASD)
    if (state[SDL_SCANCODE_W]) {
        directionsLogged.insert(std::string("W"));
        if (gControlledEntity) {
            // Move up (decrease Y)
            gControlledEntity->setY(gControlledEntity->getY() - 5.0f);
        }
    }
    else if (state[SDL_SCANCODE_S]) {
        directionsLogged.insert(std::string("S"));
        if (gControlledEntity) {
            // Move down (increase Y)
            gControlledEntity->setY(gControlledEntity->getY() + 5.0f);
        }
    }
    else {
        directionsLogged.erase(std::string("W"));
        directionsLogged.erase(std::string("S"));
    }

    if (state[SDL_SCANCODE_A]) {
        directionsLogged.insert(std::string("A"));
        if (gControlledEntity) { 
            // Move left (decrease X)
            gControlledEntity->setX(gControlledEntity->getX() - 5.0f);
        }
    }
    else if (state[SDL_SCANCODE_D])
    {
        directionsLogged.insert(std::string("D"));
        if (gControlledEntity) {
            // Move right (increase X)
            gControlledEntity->setX(gControlledEntity->getX() + 5.0f);
        }
    }
    else {
        directionsLogged.erase(std::string("A"));
        directionsLogged.erase(std::string("D"));
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
