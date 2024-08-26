#include "graphics/graphics.h"

#include <fmt/format.h>

namespace grp {
Graphics::InitializationError::InitializationError(const std::string &what_arg)
    : runtime_error(what_arg) {}

Graphics::Graphics(Graphics::Settings settings) {
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
}

Graphics::~Graphics() {
    window_.release();
    SDL_Quit();
}

void Graphics::render() {
    window_->clear();
    window_->update();
}
}  // namespace grp
