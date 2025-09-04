#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <functional>
#include <vector>
#include <string>

class Entity
{
public:
    // Constructor for static entities (matches implementation in Entity.cpp)
    Entity(std::string name, float x, float y, float width, float height, SDL_Texture *texture,
           int frameColumnCount, int frameRowCount, int animationDelay, bool isAffectedByGravity, bool isEnemy, bool isPlatform,
           const std::function<void(Entity &)> &updateFunction);

    // Constructor for Non-static entities (matches implementation in Entity.cpp)
    Entity(std::string name, float x, float y, float width, float height, float velocityX, float velocityY, float accelerationX,
           float accelerationY, bool isMovable, bool isControllable, bool isEnemy, bool isPlatform, SDL_Texture *texture,
           int frameColumnCount, int frameRowCount, int animationDelay, float scale, bool isAffectedByGravity,
           const std::function<void(Entity &)> &updateFunction);

    struct PathVector
    {
        float vx;
        float vy;
        int updates;
    };

    // Getters
    std::string getName() const;
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    float getVelocityX() const;
    float getVelocityY() const;
    float getAccelerationX() const;
    float getAccelerationY() const;
    bool isMovable() const;
    bool isControllable() const;
    bool isEnemy() const;
    bool isJumping() const;
    bool isReset() const;
    bool isPlatform() const;
    bool getisAffectedByGravity() const;
    SDL_Texture *getTexture() const;
    int getFrameColumnCount() const;
    int getFrameRowCount() const;
    int getCurrentFrameRow() const;
    int getCurrentFrameColumn() const;
    int getAnimationDelay() const;
    std::function<void(Entity &)> getUpdateFunction() const;
    float getScale() const;
    const std::vector<PathVector> &getPathVectors() const;
    int getNextPathVectorIndex() const;
    int getPathVectorUpdatesRemaining() const;
    bool hasPathVectors() const;

    // Setters
    void setName(const std::string &name);
    void setX(float x);
    void setY(float y);
    void setWidth(float width);
    void setHeight(float height);
    void setVelocityX(float velocityX);
    void setVelocityY(float velocityY);
    void setAccelerationX(float accelerationX);
    void setAccelerationY(float accelerationY);
    void setTexture(SDL_Texture *texture);
    void setMovable(bool isMovable);
    void setControllable(bool isControllable);
    void setisAffectedByGravity(bool val);
    void setEnemy(bool val);
    void setJumping(bool val);
    void setReset(bool val);
    void isPlatform(bool val);
    void setFrameColumnCount(int frameColumnCount);
    void setFrameRowCount(int frameRowCount);
    void setCurrentFrameRow(int currentFrameRow);
    void setCurrentFrameColumn(int currentFrameColumn);
    void setAnimationDelay(int animationDelay);
    void setUpdateFunction(const std::function<void(Entity &)> &updateFunction);
    void setScale(float scale);
    void setPathVectors(const std::vector<PathVector> &vectors);
    void setNextPathVectorIndex(int index);
    void setPathVectorUpdatesRemaining(int updates);

    void update();

private:
    std::string name_;

    float x_;
    float y_;

    float width_;
    float height_;

    float velocityX_;
    float velocityY_;

    float accelerationX_;
    float accelerationY_;

    bool isMovable_;
    bool isControllable_;
    bool isAffectedByGravity;
    bool isEnemy_;
    bool isJumping_;
    bool isReset_;
    bool isPlatform_;

    SDL_Texture *texture_;

    int frameColumnCount_;
    int frameRowCount_;
    int currentFrameRow_;
    int currentFrameColumn_;
    int animationDelay_;
    float scale_;

    std::function<void(Entity &)> updateFunction_;

    std::vector<PathVector> pathVectors_;
    int nextPathVectorIndex_;
    int pathVectorUpdatesRemaining_;
};

#endif
