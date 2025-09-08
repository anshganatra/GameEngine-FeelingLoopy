#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "entity.h"

namespace scaling {

enum class ScalingMode { ConstantPixels, ProportionalLogical };

struct Controller {
    ScalingMode mode = ScalingMode::ProportionalLogical;
    int logical_w = 0;
    int logical_h = 0;
    int window_scale = 1;

    static constexpr int kMinScale = 1;
    static constexpr int kMaxScale = 6;

    // Initialize baseline and apply defaults
    void init(SDL_Window* window, SDL_Renderer* renderer, int base_w, int base_h, const std::vector<Entity>& entities);

    // Apply current mode to renderer and textures
    void apply(SDL_Renderer* renderer, const std::vector<Entity>& entities) const;

    // Resize window to logical * window_scale
    void applyWindowSize(SDL_Window* window) const;

    // Change mode and re-apply
    void setMode(ScalingMode newMode, SDL_Renderer* renderer, const std::vector<Entity>& entities);

    // Handle mouse wheel to adjust window size
    void onMouseWheel(const SDL_Event& e, SDL_Window* window);
};

} // namespace scaling
