#ifndef PHYSICS_H
#define PHYSICS_H

#include "entity.h"

class Physics {
private:
    static float gravity;    // pixels per second^2
    static float deltaTime;  // seconds per frame (~1/60)
public:
    static std::pair<std::pair<float,float>, std::pair<float,float>> applyPhysics(Entity& entity);

    // Setters and getters for tuning
    static void setGravity(float g);
    static float getGravity();
    static void setDeltaTime(float dt);
    static float getDeltaTime();
};

#endif 