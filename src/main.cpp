#include "Game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init("ManPac", 800, 600)) {
      std::cerr << "Failed to initialize game." << std::endl;
      return -1;
    }

    game.run();
    game.cleanup();

    return 0;
  }
