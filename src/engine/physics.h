#ifndef PHYSICS_H
#define PHYSICS_H

#include "entity.h"

class Physics {
private:
    constexpr static float gravity = 9.81f; // Default gravity value (m/s^2)
    constexpr static float deltaTime = 0.016f; // Assuming a default frame time of ~16ms (60 FPS)
public:
    static std::pair<std::pair<float,float>, std::pair<float,float>> applyPhysics(Entity& entity);

    // Setters and getters for gravity
    // void setGravity(float g);
    float getGravity();
    // void setDeltaTime(float dt);
    float getDeltaTime();
};

#endif 