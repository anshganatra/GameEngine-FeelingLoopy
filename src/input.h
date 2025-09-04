// Lightweight input state snapshot
#pragma once

#include <SDL3/SDL.h>
#include <vector>

namespace input {

// Capture current keyboard state; call once per frame
void detect();

// Query functions
bool down(SDL_Scancode sc);
bool pressed(SDL_Scancode sc);
bool released(SDL_Scancode sc);

// List of keys currently down this frame (scancodes)
const std::vector<SDL_Scancode>& downKeys();

}