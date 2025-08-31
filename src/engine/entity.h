#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <functional>

class Entity
{
private:
    // TODO: Explore writing x,y as vectors
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
    SDL_Texture *texture_;

    int frameColumnCount_;
    int frameRowCount_;
    int currentFrameRow_;
    int currentFrameColumn_;
    int animationDelay_;
    float scale_;

    std::function<void(Entity &)> updateFunction_;

public:

    // Constructor for static entities (matches implementation in Entity.cpp)
    Entity(float x, float y, float width, float height, SDL_Texture *texture,
           int frameColumnCount, int frameRowCount, int animationDelay,
           const std::function<void(Entity &)> &updateFunction);

    // Constructor for Non-static entities (matches implementation in Entity.cpp)
    Entity(float x, float y, float width, float height, float velocityX, float velocityY, float accelerationX,
           float accelerationY, bool isMovable, bool isControllable, SDL_Texture *texture,
           int frameColumnCount, int frameRowCount, int animationDelay, float scale,
           const std::function<void(Entity &)> &updateFunction);

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
    SDL_Texture *getTexture() const;
    int getFrameColumnCount() const;
    int getFrameRowCount() const;
    int getCurrentFrameRow() const;
    int getCurrentFrameColumn() const;
    int getAnimationDelay() const;
    std::function<void(Entity &)> getUpdateFunction() const;
    float getScale() const;

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
    void setFrameColumnCount(int frameColumnCount);
    void setFrameRowCount(int frameRowCount);
    void setCurrentFrameRow(int currentFrameRow);
    void setCurrentFrameColumn(int currentFrameColumn);
    void setAnimationDelay(int animationDelay);
    void setUpdateFunction(const std::function<void(Entity &)> &updateFunction);
    void setScale(float scale);

    void update();
};

#endif
