#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class Entity
{
    private:
        //TODO: Explore writing x,y as vectors
        float x_;
        float y_;
        float width_;
        float height_;
        float velocityX_;
        float velocityY_;
        float accelerationX_;
        float accelerationY_;
        bool isMovable_;
        SDL_Texture* texture_;

    public:

        Entity(float x, float y, float width, float height, SDL_Texture* texture)
            : x_(x), y_(y), width_(width), height_(height), texture_(texture) {}

        float getX() const {
            return x_;
        }

        float getY() const {
            return y_;
        }

        float getWidth() const {
            return width_;
        }

        float getHeight() const {
            return height_;
        }

        float getVelocityX() const {
            return velocityX_;
        }

        float getVelocityY() const {
            return velocityY_;
        }

        float getAccelerationX() const {
            return accelerationX_;
        }

        float getAccelerationY() const {
            return accelerationY_;
        }

        bool isMovable() const {
            return isMovable_;
        }

        SDL_Texture* getTexture() const {
            return texture_;
        }

        void setX(float x) {
            x_ = x;
        }

        void setY(float y) {
            y_ = y;
        }

        void setWidth(float width) {
            width_ = width;
        }

        void setHeight(float height) {
            height_ = height;
        }

        void setVelocityX(float velocityX) {
            velocityX_ = velocityX;
        }

        void setVelocityY(float velocityY) {
            velocityY_ = velocityY;
        }

        void setAccelerationX(float accelerationX) {
            accelerationX_ = accelerationX;
        }

        void setAccelerationY(float accelerationY) {
            accelerationY_ = accelerationY;
        }

        void setTexture(SDL_Texture* texture) {
            texture_ = texture;
        }

        void setMovable(bool isMovable) {
            isMovable_ = isMovable;
        }
};