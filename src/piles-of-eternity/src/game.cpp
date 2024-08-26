#include "game.h"

#include <iostream>

Game::RunStatus Game::run(int argc, char *argv[]) {
    grp::Window::Settings window_settings {};
    window_settings.dimensions.size = Eigen::Vector2i(1280, 720);
    window_settings.title           = "Piles of Eternity";

    grp::Graphics::Settings graphics_settings {};
    graphics_settings.window_settings = window_settings;

    try {
        graphics_ = std::make_unique<grp::Graphics>(graphics_settings);
    } catch (const grp::Graphics::InitializationError &err) {
        std::cerr << "Graphics subsystem failed to initialize!\n" << err.what();
        return RunStatus::Fail;
    }

    graphics_->render();

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
    return RunStatus::Success;
}
