// Use Engine and Entity to create a window with three entities
#include "engine/engine.h"
#include "engine/entity.h"
#include <SDL3_image/SDL_image.h>
#include "keyboardInput.h"

const int gameWindowWidth = 1200;
const int gameWindowHeight = 800;
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
    Entity platform(std::string("Platform"), -20.0f, gameWindowHeight - 0.66f * platformTexture->h, static_cast<float>(gameWindowWidth), static_cast<float>(platformTexture->h), platformTexture, 1, 1, 0, false, [](Entity&){});
    engine.addEntity(platform);

    // Initialise Automoving entity
    SDL_Texture* droneTexture = loadTexture(renderer, "media/cyberpunk_enemy_drone_move.png");
    Entity drone(std::string("Drone"), gameWindowWidth/3, gameWindowHeight/3, droneTexture->w/8, droneTexture->h/8, 
        0, 0, 0, 0, true, false, droneTexture, 8, 8, 20, 0.5, true, [](Entity&){});
    // Define path points for the drone to follow
    // drone.setPath({{gameWindowWidth/4, gameWindowHeight/4},
    //                {gameWindowWidth/2, gameWindowHeight/2},
    //                {gameWindowWidth*2/3, gameWindowHeight/3}});
    engine.addEntity(drone);

    //Initialise Controllable Player Entity
    SDL_Texture* playerTexture = loadTexture(renderer, "media/darkworld_character_cainhurst_right.png");
    Entity player(std::string("Player"), 2*gameWindowWidth/3, gameWindowHeight/3, playerTexture->w/4, playerTexture->h, 
        0, 0, 0, 0, true, false, playerTexture, 4, 1, 33, 2, true, [](Entity&){});
    Entity* playerPtr = engine.addEntity(player);
    setControlledEntity(playerPtr);

    if (!platformTexture || !droneTexture || !playerTexture) {
        if (platformTexture) SDL_DestroyTexture(platformTexture);
        if (droneTexture) SDL_DestroyTexture(droneTexture);
        if (playerTexture) SDL_DestroyTexture(playerTexture);
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
