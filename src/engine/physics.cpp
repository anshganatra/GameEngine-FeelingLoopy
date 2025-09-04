#include "physics.h"

// Defaults tuned for pixel units: ~2000 px/s^2 feels platformer-like
float Physics::gravity = 2000.0f;
float Physics::deltaTime = 1.0f / 60.0f;

std::pair<std::pair<float,float>, std::pair<float,float>> Physics::applyPhysics(Entity& e) {
    // Read current state
    float x = e.getX();
    float y = e.getY();
    float vx = e.getVelocityX();
    float vy = e.getVelocityY();
    float ax = e.getAccelerationX();
    float ay = e.getAccelerationY();
    if (!e.isMovable()) return {{x, y}, {vx, vy}};

    // Apply gravity if the entity is affected by it
    if (e.getisAffectedByGravity()) {
        ay += gravity;
    }

    // Semi-implicit Euler integration using the entity's own acceleration
    vx += ax * deltaTime;
    vy += ay * deltaTime;

    float targetX = x + vx * deltaTime;
    float targetY = y + vy * deltaTime;

    return {{targetX, targetY}, {vx, vy}};
}

void Physics::setGravity(float g) { 
    gravity = g; 
}
float Physics::getGravity() { 
    return gravity; 
}
void Physics::setDeltaTime(float dt) { 
    deltaTime = dt; 
}
float Physics::getDeltaTime() { 
    return deltaTime; 
}
