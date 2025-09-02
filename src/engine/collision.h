// Simple collision helpers for Entities (AABB)
#ifndef COLLISION_H
#define COLLISION_H

#include <SDL3/SDL.h>
#include <utility>

#include "entity.h"

// Returns which axes overlap: {xOverlap, yOverlap}
std::pair<bool, bool> areEntitiesColliding(const Entity &a, const Entity &b);

// Move entity to target while resolving collisions; updates position and velocity
void handle_collision(Entity& e, float targetX, float targetY, float targetVx, float targetVy);

#endif // COLLISION_H
