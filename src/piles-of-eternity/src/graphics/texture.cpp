#include "graphics/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace {
SDL_Surface *load_surface(const std::filesystem::path &path) {
    int32_t width;
    int32_t height;
    int32_t channels;

    uint8_t *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    int32_t pitch = width * channels;
    pitch         = (pitch + 3) & ~3;

    int32_t r_mask, g_mask, b_mask, a_mask;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
    r_mask = 0x000000FF;
    g_mask = 0x0000FF00;
    b_mask = 0x00FF0000;
    a_mask = (channels == 4) ? 0xFF000000 : 0;
#else
    int s  = (channels == 4) ? 0 : 8;
    r_mask = 0xFF000000 >> s;
    g_mask = 0x00FF0000 >> s;
    b_mask = 0x0000FF00 >> s;
    a_mask = 0x000000FF >> s;
#endif

    return SDL_CreateRGBSurfaceFrom(data, width, height, channels * 8, pitch,
                                    r_mask, g_mask, b_mask, a_mask);
}

}  // namespace

namespace grp {
std::shared_ptr<Texture> Texture::Loader::operator()(
    const std::filesystem::path &path, SDL_Renderer *renderer) {
    auto *surface = load_surface(path);
    if (surface == nullptr) {
        return nullptr;
    }

    auto *loaded_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (loaded_texture == nullptr) {
        return nullptr;
    }

    SDL_FreeSurface(surface);

    return std::make_shared<Texture>(loaded_texture);
}

Texture::~Texture() { SDL_DestroyTexture(texture); }
}  // namespace grp