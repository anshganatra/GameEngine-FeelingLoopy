#include "entity.h"

// Constructor for the static entities
// argument types are: (std::__1::string, int, double, const int, int, SDL_Texture *, int, int, int, lambda [](Entity &)->void)
Entity::Entity(std::string name, float x, float y, float width, float height, SDL_Texture *texture, int frameColumnCount, int frameRowCount, int animationDelay, const std::function<void(Entity &)> &updateFunction)
    : 
    name_(name),
    x_(x),
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
    updateFunction_(updateFunction),
    pathPoints_(),
    nextPathIndex_(-1) {}



// Constructor for the Non-static entities
Entity::Entity(std::string name, float x, float y, float width, float height, float velocityX, float velocityY, float accelerationX,
        float accelerationY, bool isMovable, bool isControllable, SDL_Texture *texture, int frameColumnCount,
        int frameRowCount, int animationDelay, float scale, const std::function<void(Entity &)> &updateFunction)
    : name_(name),
      x_(x),
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
      updateFunction_(updateFunction),
      pathPoints_(),
      nextPathIndex_(0) {}


std::string Entity::getName() const {
    return name_;
}

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

const std::vector<SDL_FPoint>& Entity::getPath() const {
    return pathPoints_;
}

int Entity::getNextPathIndex() const {
    return nextPathIndex_;
}

bool Entity::hasPath() const {
    return !pathPoints_.empty() && nextPathIndex_ >= 0 && nextPathIndex_ < static_cast<int>(pathPoints_.size());
}

void Entity::setName(const std::string& name) {
    name_ = name;
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

void Entity::setPath(const std::vector<SDL_FPoint>& pathPoints) {
    pathPoints_ = pathPoints;
    nextPathIndex_ = pathPoints_.empty() ? -1 : 0;
}

void Entity::setNextPathIndex(int index) {
    nextPathIndex_ = index;
}

void Entity::update() {
    if (updateFunction_) {
        updateFunction_(*this);
    }
}
