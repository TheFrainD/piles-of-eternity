#pragma once

#include <memory>

#include "graphics/window.h"
#include "resource/resource_manager.h"

namespace grp {
class Graphics {
public:
    class InitializationError : public std::runtime_error {
    public:
        explicit InitializationError(const std::string &what_arg);
    };

    struct Settings {
        Window::Settings window_settings;
    };

    explicit Graphics(Settings settings,
                      res::ResourceManager &resource_manager);
    ~Graphics();

    void render();

private:
    std::unique_ptr<Window> window_;
    SDL_Renderer *renderer_;
};
}  // namespace grp