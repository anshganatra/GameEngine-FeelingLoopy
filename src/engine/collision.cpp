// Fast AABB collision helpers optimized for SDL3
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>

#include <utility>

#include "entity.h"
#include "engine.h"
#include "collision.h"

// Move until contact using overlap depth on each axis to avoid overlaps at high speed.

// Global engine instance from main.cpp
extern Engine engine;

// Move entity towards target while resolving collisions; zeroes velocity on blocked axes
// Optionally returns max penetration along X/Y at the probe position using motion directions
inline bool wouldCollideWithAny(Entity* moving, float newX, float newY,
                                float* outMaxPenX = nullptr, float* outMaxPenY = nullptr,
                                float dirX = 0.0f, float dirY = 0.0f);

// Compact helper to build an SDL_FRect from an Entity (no heap allocations)
static inline SDL_FRect makeRect(const Entity &e) {
    return SDL_FRect{ e.getX(), e.getY(), e.getWidth() * e.getScale(), e.getHeight() * e.getScale() };
}

void handle_collision(Entity& e, float targetX, float targetY, float targetVx, float targetVy) {
    float x = e.getX();
    float y = e.getY();
    const float prevVx = e.getVelocityX();
    const float prevVy = e.getVelocityY();

    // X axis: move to target or to contact using max penetration, clamped to avoid reversing
    float dx = targetX - x;
    const float dirX = (dx > 0.0f) ? 1.0f : (dx < 0.0f ? -1.0f : 0.0f);
    bool collidedX = false;
    if (dirX != 0.0f) {
        float maxPenX = 0.0f;
        collidedX = wouldCollideWithAny(&e, targetX, y, &maxPenX, nullptr, dirX, 0.0f);
        if (!collidedX) {
            x = targetX;
        } else {
            const float backoff = SDL_min(SDL_fabsf(dx), maxPenX);
            const float candidate = targetX - dirX * backoff;
            // Clamp to not pass the starting point
            x = (dirX > 0.0f) ? SDL_max(candidate, e.getX()) : SDL_min(candidate, e.getX());
        }
    }

    // Y axis: move to target or to contact similarly, using updated X
    float dy = targetY - y;
    const float dirY = (dy > 0.0f) ? 1.0f : (dy < 0.0f ? -1.0f : 0.0f);
    bool collidedY = false;
    if (dirY != 0.0f) {
        float maxPenY = 0.0f;
        collidedY = wouldCollideWithAny(&e, x, targetY, nullptr, &maxPenY, 0.0f, dirY);
        if (!collidedY) {
            y = targetY;
        } else {
            const float backoff = SDL_min(SDL_fabsf(dy), maxPenY);
            const float candidate = targetY - dirY * backoff;
            y = (dirY > 0.0f) ? SDL_max(candidate, e.getY()) : SDL_min(candidate, e.getY());
        }
    }

    // Commit. Keep previous velocity on axes that collided; otherwise take target velocity
    e.setX(x);
    e.setY(y);
    if(e.isControllable()) {
        e.setVelocityX(collidedX ? 0 : targetVx);
        e.setVelocityY(collidedY ? 0 : targetVy);
    } else {
        e.setVelocityX(collidedX ? prevVx : targetVx);
        e.setVelocityY(collidedY ? prevVy : targetVy);
    }
}


// Check if moving entity to (newX, newY) would collide with any other entity
inline bool wouldCollideWithAny(Entity* moving, float newX, float newY,
                                float* outMaxPenX, float* outMaxPenY,
                                float dirX, float dirY) {
    if (!moving) return false;
    Entity next = *moving; // lightweight copy with proposed position
    next.setX(newX);
    next.setY(newY);

    const SDL_FRect pr = makeRect(next);
    bool collided = false;
    float maxPenX = 0.0f;
    float maxPenY = 0.0f;

    const auto& entities = engine.getEntities();
    for (const auto& other : entities) {
        if(other.isDisabled()) continue;
        if (&other == moving) continue;
        const SDL_FRect orc = makeRect(other);
        const bool xOverlap = (pr.x < orc.x + orc.w) && (pr.x + pr.w > orc.x);
        const bool yOverlap = (pr.y < orc.y + orc.h) && (pr.y + pr.h > orc.y);
        if (!(xOverlap && yOverlap) || !other.isCollidable()) continue;

        if(other.isEnemy() && moving->isControllable()) {
            moving->setReset(true);
            break;
        } 
        
        if(other.isPlatform() && moving->isControllable()) {
            moving->setJumping(false);
        }

        other.getUpdateFunction()(const_cast<Entity&>(other)); // Call on-collision update function

        collided = true;
        if (outMaxPenX && dirX != 0.0f) {
            const float penX = (dirX > 0.0f) ? ((pr.x + pr.w) - orc.x) : ((orc.x + orc.w) - pr.x);
            if (penX > maxPenX) maxPenX = penX;
        }
        if (outMaxPenY && dirY != 0.0f) {
            const float penY = (dirY > 0.0f) ? ((pr.y + pr.h) - orc.y) : ((orc.y + orc.h) - pr.y);
            if (penY > maxPenY) maxPenY = penY;
        }
    }

    if (outMaxPenX) *outMaxPenX = maxPenX;
    if (outMaxPenY) *outMaxPenY = maxPenY;
    
    return collided;
}