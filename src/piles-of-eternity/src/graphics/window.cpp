#include "graphics/window.h"

#include <fmt/format.h>

namespace grp {
Window::InitializationError::InitializationError(const std::string &what_arg)
    : runtime_error(what_arg) {}

Window::Window(Settings settings) {
    auto dimensions = settings.dimensions;

    if (dimensions.size.x() < 0 || dimensions.size.y() < 0 ||
        dimensions.position.x() < 0 || dimensions.position.y() < 0) {
        throw InitializationError {"Wrong dimensions!"};
    }

    auto flags = SDL_WINDOW_SHOWN | static_cast<uint32_t>(settings.mode);
    window_ = SDL_CreateWindow(settings.title.c_str(), dimensions.position.x(),
                               dimensions.position.y(), dimensions.size.x(),
                               dimensions.size.y(), flags);

    if (window_ == nullptr) {
        throw InitializationError {fmt::format(
            "SDL window initialization failed! SDL Error: {}", SDL_GetError())};
    }
}

void Window::update() const { SDL_UpdateWindowSurface(window_); }

Window::~Window() {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
}

SDL_Renderer *Window::create_renderer() {
    return SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
}
}  // namespace grp
