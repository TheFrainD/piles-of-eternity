#include "graphics/graphics.h"

#include <fmt/format.h>

#include "graphics/texture.h"

static std::shared_ptr<grp::Texture> texture;

namespace grp {
Graphics::InitializationError::InitializationError(const std::string &what_arg)
    : runtime_error(what_arg) {}

Graphics::Graphics(Graphics::Settings settings,
                   res::ResourceManager &resource_manager) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw InitializationError {fmt::format(
            "Failed to initialize SDL! SDL error: {}", SDL_GetError())};
    }

    try {
        window_ = std::make_unique<Window>(settings.window_settings);
    } catch (const Window::InitializationError &err) {
        throw InitializationError {
            fmt::format("Window error!\n{}", err.what())};
    }

    renderer_ = window_->create_renderer();
    if (renderer_ == nullptr) {
        throw InitializationError {
            fmt::format("Failed to initialize SDL Renderer! SDL Error: {}",
                        SDL_GetError())};
    }

    SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

    texture = resource_manager.load_resource<Texture, Texture::Loader>(
        "test", "./test.png", renderer_);
    if (texture == nullptr) {
        throw InitializationError {"Failed to load image!"};
    }
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer_);
    window_.release();
    SDL_Quit();
}

void Graphics::render() {
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, texture->texture, nullptr, nullptr);
    SDL_RenderPresent(renderer_);
}
}  // namespace grp
