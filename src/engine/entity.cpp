#include "entity.h"

// Constructor for the static entities
Entity::Entity(std::string name, float x, float y, float width, float height, SDL_Texture *texture, int frameColumnCount, int frameRowCount, int animationDelay, bool isAffectedByGravity, bool isEnemy, bool isPlatform, const std::function<void(Entity &)> &updateFunction)
    : name_(name),
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
      isEnemy_(isEnemy),
      isJumping_(false),
      isReset_(false),
      isPlatform_(isPlatform),
      isDisabled_(false),
      isCollidable_(true),
      texture_(texture),
      frameColumnCount_(frameColumnCount),
      frameRowCount_(frameRowCount),
      currentFrameRow_(0),
      currentFrameColumn_(0),
      animationDelay_(animationDelay),
      scale_(1.0f),
      isAffectedByGravity(isAffectedByGravity),
      updateFunction_(updateFunction),
      pathVectors_(),
      nextPathVectorIndex_(-1),
      pathVectorUpdatesRemaining_(0) {}

// Constructor for the Non-static entities
Entity::Entity(std::string name, float x, float y, float width, float height, float velocityX, float velocityY, float accelerationX,
               float accelerationY, bool isMovable, bool isControllable, bool isEnemy, bool isPlatform, bool isCollidable, SDL_Texture *texture, int frameColumnCount,
               int frameRowCount, int animationDelay, float scale, bool isAffectedByGravity, const std::function<void(Entity &)> &updateFunction)
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
      isEnemy_(isEnemy),
      isJumping_(false),
      isReset_(false),
      isPlatform_(isPlatform),
      isCollidable_(isCollidable),
      isDisabled_(false),
      texture_(texture),
      frameColumnCount_(frameColumnCount),
      frameRowCount_(frameRowCount),
      currentFrameRow_(0),
      currentFrameColumn_(0),
      animationDelay_(animationDelay),
      scale_(scale),
      isAffectedByGravity(isAffectedByGravity),
      updateFunction_(updateFunction),
      pathVectors_(),
      nextPathVectorIndex_(-1),
      pathVectorUpdatesRemaining_(0) {}

std::string Entity::getName() const
{
    return name_;
}

float Entity::getX() const
{
    return x_;
}

float Entity::getY() const
{
    return y_;
}

float Entity::getWidth() const
{
    return width_;
}

float Entity::getHeight() const
{
    return height_;
}

float Entity::getVelocityX() const
{
    return velocityX_;
}

float Entity::getVelocityY() const
{
    return velocityY_;
}

float Entity::getAccelerationX() const
{
    return accelerationX_;
}

float Entity::getAccelerationY() const
{
    return accelerationY_;
}

bool Entity::isMovable() const
{
    return isMovable_;
}

bool Entity::isControllable() const
{
    return isControllable_;
}

bool Entity::isEnemy() const
{
    return isEnemy_;
}

bool Entity::isJumping() const
{
    return isJumping_;
}

bool Entity::isPlatform() const
{
    return isPlatform_;
}

bool Entity::isReset() const
{
    return isReset_;
}

bool Entity::isCollidable() const
{
    return isCollidable_;
}

bool Entity::isDisabled() const
{
    return isDisabled_;
}

bool Entity::getisAffectedByGravity() const
{
    return isAffectedByGravity;
}

SDL_Texture *Entity::getTexture() const
{
    return texture_;
}

int Entity::getFrameColumnCount() const
{
    return frameColumnCount_;
}

int Entity::getFrameRowCount() const
{
    return frameRowCount_;
}

int Entity::getCurrentFrameRow() const
{
    return currentFrameRow_;
}

int Entity::getCurrentFrameColumn() const
{
    return currentFrameColumn_;
}

int Entity::getAnimationDelay() const
{
    return animationDelay_;
}

float Entity::getScale() const
{
    return scale_;
}

std::function<void(Entity &)> Entity::getUpdateFunction() const
{
    return updateFunction_;
}

const std::vector<Entity::PathVector> &Entity::getPathVectors() const { return pathVectors_; }
int Entity::getNextPathVectorIndex() const { return nextPathVectorIndex_; }
int Entity::getPathVectorUpdatesRemaining() const { return pathVectorUpdatesRemaining_; }
bool Entity::hasPathVectors() const { return !pathVectors_.empty() && nextPathVectorIndex_ >= 0 && nextPathVectorIndex_ < (int)pathVectors_.size(); }

void Entity::setName(const std::string &name)
{
    name_ = name;
}

void Entity::setX(float x)
{
    x_ = x;
}

void Entity::setY(float y)
{
    y_ = y;
}

void Entity::setWidth(float width)
{
    width_ = width;
}

void Entity::setHeight(float height)
{
    height_ = height;
}

void Entity::setVelocityX(float velocityX)
{
    velocityX_ = velocityX;
}

void Entity::setVelocityY(float velocityY)
{
    velocityY_ = velocityY;
}

void Entity::setAccelerationX(float accelerationX)
{
    accelerationX_ = accelerationX;
}

void Entity::setAccelerationY(float accelerationY)
{
    accelerationY_ = accelerationY;
}

void Entity::setTexture(SDL_Texture *texture)
{
    texture_ = texture;
}

void Entity::setMovable(bool isMovable)
{
    isMovable_ = isMovable;
}

void Entity::setControllable(bool isControllable)
{
    isControllable_ = isControllable;
}

void Entity::setEnemy(bool val)
{
    isEnemy_ = val;
}

void Entity::setJumping(bool val)
{
    isJumping_ = val;
}

void Entity::setReset(bool val)
{
    isReset_ = val;
}

void Entity::isPlatform(bool val)
{
    isPlatform_ = val;
}

void Entity::isCollidable(bool val)
{
    isCollidable_ = val;
}

void Entity::setisAffectedByGravity(bool val)
{
    isAffectedByGravity = val;
}

void Entity::setDisabled(bool val)
{
    isDisabled_ = val;
}

void Entity::setFrameColumnCount(int frameColumnCount)
{
    frameColumnCount_ = frameColumnCount;
}

void Entity::setFrameRowCount(int frameRowCount)
{
    frameRowCount_ = frameRowCount;
}

void Entity::setCurrentFrameRow(int currentFrameRow)
{
    currentFrameRow_ = currentFrameRow;
}

void Entity::setCurrentFrameColumn(int currentFrameColumn)
{
    currentFrameColumn_ = currentFrameColumn;
}

void Entity::setAnimationDelay(int animationDelay)
{
    animationDelay_ = animationDelay;
}

void Entity::setScale(float scale)
{
    scale_ = scale;
}

void Entity::setUpdateFunction(const std::function<void(Entity &)> &updateFunction)
{
    updateFunction_ = updateFunction;
}

void Entity::setPathVectors(const std::vector<PathVector> &vectors)
{
    pathVectors_ = vectors;
    if (pathVectors_.empty())
    {
        nextPathVectorIndex_ = -1;
        pathVectorUpdatesRemaining_ = 0;
    }
    else
    {
        nextPathVectorIndex_ = 0;
        pathVectorUpdatesRemaining_ = 0; // will be initialized on first step
    }
}

void Entity::setNextPathVectorIndex(int index) { nextPathVectorIndex_ = index; }
void Entity::setPathVectorUpdatesRemaining(int updates) { pathVectorUpdatesRemaining_ = updates; }

void Entity::update()
{
    if (updateFunction_)
    {
        updateFunction_(*this);
    }
}