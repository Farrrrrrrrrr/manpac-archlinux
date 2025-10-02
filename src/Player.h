#pragma once
#include <SDL2/SDL.h>
#include "Map.h"

class Player {
  public:
    void setPosition(int x, int y);
    void handleInput(SDL_Event& event, Map& map);
    void render(SDL_Renderer* renderer, SDL_Texture* texture);

    int getX() const {return x;}
    int getY() const {return y;}

  private:
    int x = 1, y = 1;
};
