#include <SDL.h>
#include <SDL_rect.h>
#include "entity.h" // Assumes Entity is defined in entity.h

// Checks if two entities are colliding using their SDL_Rect bounds
bool areEntitiesColliding(const Entity& a, const Entity& b) {
    SDL_FRect *aRect = getRect(a);
    SDL_FRect *bRect = getRect(b);
    
    bool isColliding = SDL_HasRectIntersectionFloat(aRect, bRect);
    
    delete(aRect);
    delete(bRect);

    return isColliding;
}

// Converts an Entity's position and size to an SDL_FRect
SDL_FRect *getRect(const Entity& entity) {
    SDL_FRect *rect = new SDL_FRect();
    rect->x = entity.getX();
    rect->y = entity.getY();
    rect->w = entity.getWidth();
    rect->h = entity.getHeight();
    
    return rect;
}
