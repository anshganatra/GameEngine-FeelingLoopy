// Input detection implementation
#include "input.h"

#include <bitset>

namespace input {

static std::bitset<SDL_SCANCODE_COUNT> gPrev;
static std::bitset<SDL_SCANCODE_COUNT> gCurr;
static std::vector<SDL_Scancode> gDownList;

void detect()
{
    gPrev = gCurr;
    const bool* state = SDL_GetKeyboardState(nullptr);
    gDownList.clear();
    // SDL scancode space is small; iterate directly for cache-friendly update
    for (int i = 0; i < SDL_SCANCODE_COUNT; ++i) {
        bool v = state[i];
        if (v && !gPrev.test(i)) {
            const char* name = SDL_GetScancodeName(static_cast<SDL_Scancode>(i));
            // SDL_Log("Key pressed: %s", (name && *name) ? name : "Unknown");
        }
        gCurr.set(i, v);
        if (v) gDownList.push_back(static_cast<SDL_Scancode>(i));
    }
}

bool down(SDL_Scancode sc)      { return gCurr.test(static_cast<size_t>(sc)); }
bool pressed(SDL_Scancode sc)   { size_t i = static_cast<size_t>(sc); return gCurr.test(i) && !gPrev.test(i); }
bool released(SDL_Scancode sc)  { size_t i = static_cast<size_t>(sc); return !gCurr.test(i) && gPrev.test(i); }

const std::vector<SDL_Scancode>& downKeys() { return gDownList; }

} // namespace input
