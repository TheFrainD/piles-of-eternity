#include <iostream>

#include "game.h"

int main(int argc, char *args[]) {
    Game game;
    if (game.run(argc, args) != Game::RunStatus::Success) {
        std::cerr << "Failed to run the game!\n";
    }
    return 0;
}
