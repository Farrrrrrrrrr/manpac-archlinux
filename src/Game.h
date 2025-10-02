#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Map.h"
#include "Player.h"

class Game {
  public:
    Game();
    ~Game() = default; 
    bool init(const char* title, int width, int height);
    void run();
    void cleanup();

  private:
    void processInput();
    void update();
    void render();

    SDL_Window* window;
    SDL_Renderer* renderer;

    TTF_Font* font;

    bool running;
    Player pacman;
    Map map;
    int score;
    int lives;
    SDL_Texture* pacTexture;
};

#endif // GAME_H
