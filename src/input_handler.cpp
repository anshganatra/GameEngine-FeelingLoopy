// Gameplay input handling built on top of input detection
#include "input_handler.h"
#include "input.h"

#include <unordered_map>

namespace input_handler {

// Internal state
static Entity* gControlledEntity = nullptr;
static bool gPaused = false;


// Tunables
static float gMoveSpeed = 300.0f;   // px/s
static float gJumpImpulse = 800.0f; // px/s

void setControlledEntity(Entity* e) { gControlledEntity = e; }

// Key mapping storage
static input_handler::KeyMap gDefaultMap{ SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE };
static std::unordered_map<const Entity*, input_handler::KeyMap> gEntityKeymaps;

void setKeyMapFor(Entity* e, const input_handler::KeyMap& map) {
    if (e) gEntityKeymaps[e] = map;
}
void clearKeyMapFor(Entity* e) {
    if (e) gEntityKeymaps.erase(e);
}
void setDefaultKeyMap(const input_handler::KeyMap& map) {
    gDefaultMap = map;
}

static const input_handler::KeyMap& keymapFor(const Entity* e) {
    auto it = gEntityKeymaps.find(e);
    if (it != gEntityKeymaps.end()) return it->second;
    return gDefaultMap;
}

static void applyMovement(Entity* ent, const input_handler::KeyMap& km)
{
    if (!ent) return;

    const bool up = input::down(km.up);
    const bool down = input::down(km.down);
    const bool left = input::down(km.left);
    const bool right = input::down(km.right);

    // Horizontal velocity
    float vx = 0.0f;
    if (left && !right)  vx = -gMoveSpeed;
    if (right && !left)  vx =  gMoveSpeed;
    ent->setVelocityX(vx);

    // Vertical for top-down; jump edge for platformer
    if (!ent->getisAffectedByGravity()) {
        float vy = 0.0f;
        if (up && !down)    vy = -gMoveSpeed;
        if (down && !up)    vy =  gMoveSpeed;
        ent->setVelocityY(vy);
    } else {
        if (input::pressed(km.jump) && ent->isJumping() == false) {
            ent->setVelocityY(-gJumpImpulse);
            ent->setJumping(true);
        }
    }
}

void handleInput()
{
    // Toggle pause on Escape (edge)
    if (input::pressed(SDL_SCANCODE_ESCAPE)) {
        gPaused = !gPaused;
        SDL_Log("%s", gPaused ? "Paused" : "Resumed");
    }

    // If explicit controlled entity is set, drive it with its map.
    if (gControlledEntity) {
        applyMovement(gControlledEntity, keymapFor(gControlledEntity));
    }

    // Also support driving any additionally registered entities (e.g., second player)
    for (auto& kv : gEntityKeymaps) {
        const Entity* entKey = kv.first;
        if (entKey != gControlledEntity) {
            // cast away const: our API stores const key only for map key stability
            applyMovement(const_cast<Entity*>(entKey), kv.second);
        }
    }
}

void handleEvent(const SDL_Event& e)
{
    if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float mx = 0.0f, my = 0.0f;
        SDL_GetMouseState(&mx, &my);
        if (e.button.button == SDL_BUTTON_LEFT) {
            SDL_Log("Left Mouse Button Clicked at X: %f, Y: %f", mx, my);
        } else if (e.button.button == SDL_BUTTON_RIGHT) {
            SDL_Log("Right Mouse Button Clicked at X: %f, Y: %f", mx, my);
        } else if (e.button.button == SDL_BUTTON_MIDDLE) {
            SDL_Log("Middle Mouse Button Clicked at X: %f, Y: %f", mx, my);
        }
    }
}

bool isPaused() { return gPaused; }

}
