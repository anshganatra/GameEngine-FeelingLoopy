#include "entity.h"

// Constructor for the static entities
Entity::Entity(float x, float y, float width, float height, SDL_Texture *texture, int frameColumnCount, int frameRowCount, int animationDelay, const std::function<void(Entity &)> &updateFunction)
    : x_(x),
    y_(y),
    width_(width),
    height_(height),
    velocityX_(0.0f),
    velocityY_(0.0f),
    accelerationX_(0.0f),
    accelerationY_(0.0f),
    isMovable_(false),
    isControllable_(false),
    texture_(texture),
    frameColumnCount_(frameColumnCount),
    frameRowCount_(frameRowCount),
    currentFrameRow_(0),
    currentFrameColumn_(0),
    animationDelay_(animationDelay),
    scale_(1.0f),
    updateFunction_(updateFunction) {}


// Constructor for the Non-static entities
Entity::Entity(float x, float y, float width, float height, float velocityX, float velocityY, float accelerationX,
        float accelerationY, bool isMovable, bool isControllable, SDL_Texture *texture, int frameColumnCount,
        int frameRowCount, int animationDelay, float scale, const std::function<void(Entity &)> &updateFunction)
    : x_(x),
      y_(y),
      width_(width),
      height_(height),
      velocityX_(velocityX),
      velocityY_(velocityY),
      accelerationX_(accelerationX),
      accelerationY_(accelerationY),
      isMovable_(isMovable),
      isControllable_(isControllable),
      texture_(texture),
      frameColumnCount_(frameColumnCount),
      frameRowCount_(frameRowCount),
      currentFrameRow_(0),
      currentFrameColumn_(0),
      animationDelay_(animationDelay),
      scale_(scale),
      updateFunction_(updateFunction) {}


float Entity::getX() const {
    return x_;
}

float Entity::getY() const {
    return y_;
}

float Entity::getWidth() const {
    return width_;
}

float Entity::getHeight() const {
    return height_;
}

float Entity::getVelocityX() const {
    return velocityX_;
}

float Entity::getVelocityY() const {
    return velocityY_;
}

float Entity::getAccelerationX() const {
    return accelerationX_;
}

float Entity::getAccelerationY() const {
    return accelerationY_;
}

bool Entity::isMovable() const {
    return isMovable_;
}

bool Entity::isControllable() const {
    return isControllable_;
}

SDL_Texture* Entity::getTexture() const {
    return texture_;
}

int Entity::getFrameColumnCount() const {
    return frameColumnCount_;
}

int Entity::getFrameRowCount() const {
    return frameRowCount_;
}

int Entity::getCurrentFrameRow() const {
    return currentFrameRow_;
}

int Entity::getCurrentFrameColumn() const {
    return currentFrameColumn_;
}

int Entity::getAnimationDelay() const {
    return animationDelay_;
}

float Entity::getScale() const {
    return scale_;
}

std::function<void(Entity&)> Entity::getUpdateFunction() const {
    return updateFunction_;
}

void Entity::setX(float x) {
    x_ = x;
}

void Entity::setY(float y) {
    y_ = y;
}

void Entity::setWidth(float width) {
    width_ = width;
}

void Entity::setHeight(float height) {
    height_ = height;
}

void Entity::setVelocityX(float velocityX) {
    velocityX_ = velocityX;
}

void Entity::setVelocityY(float velocityY) {
    velocityY_ = velocityY;
}

void Entity::setAccelerationX(float accelerationX) {
    accelerationX_ = accelerationX;
}

void Entity::setAccelerationY(float accelerationY) {
    accelerationY_ = accelerationY;
}

void Entity::setTexture(SDL_Texture* texture) {
    texture_ = texture;
}

void Entity::setMovable(bool isMovable) {
    isMovable_ = isMovable;
}

void Entity::setControllable(bool isControllable) {
    isControllable_ = isControllable;
}

void Entity::setFrameColumnCount(int frameColumnCount) {
    frameColumnCount_ = frameColumnCount;
}

void Entity::setFrameRowCount(int frameRowCount) {
    frameRowCount_ = frameRowCount;
}

void Entity::setCurrentFrameRow(int currentFrameRow) {
    currentFrameRow_ = currentFrameRow;
}

void Entity::setCurrentFrameColumn(int currentFrameColumn) {
    currentFrameColumn_ = currentFrameColumn;
}

void Entity::setAnimationDelay(int animationDelay) {
    animationDelay_ = animationDelay;
}

void Entity::setScale(float scale) {
    scale_ = scale;
}

void Entity::setUpdateFunction(const std::function<void(Entity&)>& updateFunction) {
    updateFunction_ = updateFunction;
}

void Entity::update() {
    if (updateFunction_) {
        updateFunction_(*this);
    }
}
