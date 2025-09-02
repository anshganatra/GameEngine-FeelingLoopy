// Fast AABB collision helpers optimized for SDL3
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>

#include <utility>

#include "entity.h"
#include "engine.h"
#include "collision.h"

// Global engine instance from main.cpp
extern Engine engine;

// Move entity towards target while resolving collisions; zeroes velocity on blocked axes
inline bool wouldCollideWithAny(const Entity* moving, float newX, float newY);

void handle_collision(Entity& e, float targetX, float targetY, float targetVx, float targetVy) {
    float x = e.getX();
    float y = e.getY();
    float vx = e.getVelocityX();
    float vy = e.getVelocityY();

    if (!wouldCollideWithAny(&e, targetX, targetY)) {
        x = targetX;
        y = targetY;
        vx = targetVx;
        vy = targetVy;
    } else {
        // Axis-separated resolution: try X, then Y; zero velocity on blocked axis
        if (!wouldCollideWithAny(&e, targetX, y)) {
            x = targetX;
            vx = targetVx;
        } else {
            vx = 0.0f;
        }

        if (!wouldCollideWithAny(&e, x, targetY)) {
            y = targetY;
            vy = targetVy;
        } else {
            vy = 0.0f;
        }
    }

    e.setX(x);
    e.setY(y);
    e.setVelocityX(vx);
    e.setVelocityY(vy);
}


// Check if moving entity to (newX, newY) would collide with any other entity
inline bool wouldCollideWithAny(const Entity* moving, float newX, float newY) {
    if (!moving) return false;
    Entity next = *moving; // lightweight copy with proposed position
    next.setX(newX);
    next.setY(newY);

    const auto& entities = engine.getEntities();
    for (const auto& other : entities) {
        if (&other == moving) continue;
        auto overlap = areEntitiesColliding(next, other);
        if (overlap.first && overlap.second) {
            return true;
        }
    }
    return false;
}

// Compact helper to build an SDL_FRect from an Entity (no heap allocations)
static inline SDL_FRect makeRect(const Entity &e) {
    return SDL_FRect{ e.getX(), e.getY(), e.getWidth() * e.getScale(), e.getHeight() * e.getScale() };
}

// Returns which axes overlap: {xOverlap, yOverlap}
std::pair<bool, bool> areEntitiesColliding(const Entity &a, const Entity &b) {
    const SDL_FRect ar = makeRect(a);
    const SDL_FRect br = makeRect(b);

    // Using direct comparisons is faster than calling into SDL for simple AABB
    const bool xOverlap = (ar.x < br.x + br.w) && (ar.x + ar.w > br.x);
    const bool yOverlap = (ar.y < br.y + br.h) && (ar.y + ar.h > br.y);
    return {xOverlap, yOverlap};
}
