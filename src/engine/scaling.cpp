// Scaling controller implementation
#include "scaling.h"

namespace scaling {

void Controller::init(SDL_Window* window, SDL_Renderer* renderer, int base_w, int base_h, const std::vector<Entity>& entities)
{
    logical_w = base_w;
    logical_h = base_h;
    window_scale = 1;
    mode = ScalingMode::ProportionalLogical;
    apply(renderer, entities);
    applyWindowSize(window);
}

void Controller::apply(SDL_Renderer* renderer, const std::vector<Entity>& entities) const
{
    if (!renderer) return;
    if (mode == ScalingMode::ProportionalLogical) {
        SDL_SetRenderLogicalPresentation(renderer, logical_w, logical_h, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        SDL_SetDefaultTextureScaleMode(renderer, SDL_SCALEMODE_LINEAR);
        for (auto &e : entities) {
            if (SDL_Texture *tex = e.getTexture()) {
                SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_LINEAR);
            }
        }
    } else {
        SDL_SetRenderLogicalPresentation(renderer, 0, 0, SDL_LOGICAL_PRESENTATION_DISABLED);
        SDL_SetDefaultTextureScaleMode(renderer, SDL_SCALEMODE_NEAREST);
        for (auto &e : entities) {
            if (SDL_Texture *tex = e.getTexture()) {
                SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
            }
        }
    }
}

void Controller::applyWindowSize(SDL_Window* window) const
{
    if (!window) return;
    const int target_w = logical_w * window_scale;
    const int target_h = logical_h * window_scale;
    SDL_SetWindowSize(window, target_w, target_h);
}

void Controller::setMode(ScalingMode newMode, SDL_Renderer* renderer, const std::vector<Entity>& entities)
{
    if (mode == newMode) return;
    mode = newMode;
    apply(renderer, entities);
}

void Controller::onMouseWheel(const SDL_Event& e, SDL_Window* window)
{
    if (e.type != SDL_EVENT_MOUSE_WHEEL) return;
    if (e.wheel.y > 0 && window_scale < kMaxScale) {
        ++window_scale;
        applyWindowSize(window);
    } else if (e.wheel.y < 0 && window_scale > kMinScale) {
        --window_scale;
        applyWindowSize(window);
    }
}

}