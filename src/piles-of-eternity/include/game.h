#pragma once

#include "graphics/graphics.h"
#include "resource/resource_manager.h"

class Game {
public:
    enum class RunStatus { Success, Fail };

    Game() = default;

    RunStatus run(int argc, char *argv[]);

private:
    res::ResourceManager resource_manager_;
    std::unique_ptr<grp::Graphics> graphics_;
};