// Use Engine and Entity to create a window with three entities
#include "engine/engine.h"
#include "engine/entity.h"
#include <SDL3_image/SDL_image.h>
#include "input_handler.h"

const int gameWindowWidth = 1200;
const int gameWindowHeight = 800;
// float globalScale = 1.0f;
// float globalScale = 1.0f;
const static char* gameWindowTitle = "Feeling Loopy";
Engine engine;
SDL_Renderer* renderer;

static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Texture* tex = IMG_LoadTexture(renderer, path);
    if (!tex) {
        SDL_Log("Failed to load %s: %s", path, SDL_GetError());
    }
    return tex;
}

void initialiseEntities() {
    //Initialise Static Platform
    SDL_Texture* platformTexture = loadTexture(renderer, "media/wilderkin_platform_basicground_idle.png");
    Entity platform(std::string("Platform"), -20.0f, gameWindowHeight - 0.20f * platformTexture->h, static_cast<float>(gameWindowWidth*2.0), static_cast<float>(platformTexture->h), platformTexture, 1, 1, 0, false, false, true, [](Entity&){});
    engine.addEntity(platform);

    // Initialise Automoving entity
    SDL_Texture* droneTexture = loadTexture(renderer, "media/cyberpunk_enemy_drone_move.png");
    Entity drone(std::string("Drone"), 30, 30, droneTexture->w/8, droneTexture->h/8, 
        0, 0, 0, 0, true, false, true, false, droneTexture, 8, 8, 10, 0.3, false,  [](Entity&){});
    // Define velocity vectors (vx, vy) with number of updates for the drone
    std::vector<Entity::PathVector> pathVectors = {
        Entity::PathVector{25.0f, 0.0f, 1000},   // move right
        Entity::PathVector{0.0f, 40.0f, 500},    // move down
        Entity::PathVector{25.0f, -25.0f, 700}   // move up-left diagonally
    };
    drone.setPathVectors(pathVectors);
    engine.addEntity(drone);

    SDL_Texture* movingPlatformTexture = loadTexture(renderer, "media/wilderkin_platform_basicground_idle.png");
    Entity movingPlatform = Entity(std::string("movingPlatform"), 10, 250, movingPlatformTexture->w, movingPlatformTexture->h, 
        0, 0, 0, 0, true, false, false, true, movingPlatformTexture, 1, 0, 0, 0.075, false,  [](Entity&){});
    std::vector<Entity::PathVector> pathVectorsPlatform = {
        Entity::PathVector{25.0f, 0.0f, 2000},   // move right
        Entity::PathVector{-25.0f, 0.0f, 2000},    // move left
    };
    movingPlatform.setPathVectors(pathVectorsPlatform);
    engine.addEntity(movingPlatform);

    SDL_Texture* movingPlatformTexture1 = loadTexture(renderer, "media/wilderkin_platform_basicground_idle.png");
    Entity movingPlatform1 = Entity(std::string("movingPlatform1"), gameWindowWidth-10, 450, movingPlatformTexture1->w, movingPlatformTexture1->h, 
        0, 0, 0, 0, true, false, false, true, movingPlatformTexture1, 1, 0, 0, 0.075, false,  [](Entity&){});
    std::vector<Entity::PathVector> pathVectorsPlatform1 = {
        Entity::PathVector{-25.0f, 0.0f, 2000},   // move right
        Entity::PathVector{25.0f, 0.0f, 2000},    // move left
    };
    movingPlatform1.setPathVectors(pathVectorsPlatform1);
    engine.addEntity(movingPlatform1);

    //Initialise Controllable Player Entity
    SDL_Texture* playerTexture = loadTexture(renderer, "media/darkworld_character_cainhurst_right.png");
    Entity player(std::string("Player"), 2*gameWindowWidth/3, gameWindowHeight/3, playerTexture->w/4, playerTexture->h, 
        0, 0, 0, 0, true, true, false, false, playerTexture, 4, 1, 20, 1.5, true, [](Entity&){});

    Entity* playerPtr = engine.addEntity(player);
    input_handler::setControlledEntity(playerPtr);

    //setControlledEntity(playerPtr);            // legacy keyboard input module

    input_handler::setControlledEntity(playerPtr); // new input handler module
    //input_handler::setKeyMapFor(playerPtr, input_handler::KeyMap{ SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_LSHIFT });

    if (!platformTexture || !droneTexture || !playerTexture || !movingPlatformTexture) {
        if (platformTexture) SDL_DestroyTexture(platformTexture);
        if (droneTexture) SDL_DestroyTexture(droneTexture);
        if (playerTexture) SDL_DestroyTexture(playerTexture);
        if( movingPlatformTexture) SDL_DestroyTexture(movingPlatformTexture);
        if( movingPlatformTexture) SDL_DestroyTexture(movingPlatformTexture);
        SDL_Log("Failed to load one or more textures: %s", SDL_GetError());
        return;
    }
}

int main(int, char**) {
    if (!engine.init(gameWindowTitle, gameWindowWidth, gameWindowHeight)) {
        return 1;
    }
    renderer = engine.getRenderer();

    initialiseEntities();

    engine.run();

    engine.cleanup();
    return 0;
}
