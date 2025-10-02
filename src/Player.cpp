#include "Player.h"

const int TILE_SIZE = 32; // Assuming each tile is 32x32 pixels
                          // Adjust as necessary
                          //
void Player::setPosition(int xPos, int yPos) {
  x = xPos;
  y = yPos;
}

void Player::handleInput(SDL_Event & event, Map& map) {
  if (event.type != SDL_KEYDOWN) return;

  int newX = x, newY = y;
  switch (event.key.keysym.sym) {
    case SDLK_UP:    newY--; break;
    case SDLK_DOWN:  newY++; break;
    case SDLK_LEFT:  newX--; break;
    case SDLK_RIGHT: newX++; break;
  }

  if (map.getTile(newY, newX) != WALL) {
    x = newX;
    y = newY;
  }
}

void Player::render(SDL_Renderer* renderer, SDL_Texture* texture) {
  SDL_Rect rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
  if (texture) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
  } else {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
  }
}
