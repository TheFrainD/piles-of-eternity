#pragma once

#include <SDL.h>

#include <filesystem>
#include <memory>

namespace grp {
struct Texture {
    class Loader {
    public:
        std::shared_ptr<Texture> operator()(const std::filesystem::path &path,
                                            SDL_Renderer *renderer);
    };

    ~Texture();

    SDL_Texture *texture;
};
}  // namespace grp