#include "Map.h"
#include <fstream>
#include <iostream>

const int TILE_SIZE = 32; // Size of each tile in pixels
                          
bool Map::load(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open map file: " << filename << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::vector<Tile> row;
    for (char c : line) {
      if (c =='#') row.push_back(WALL);
      else if (c == '.') row.push_back(PELLET);
      else row.push_back(EMPTY);
    }


    grid.push_back(row);

  }

  height = grid.size();
  if (height > 0) {
    width = grid[0].size();
  } else {
    width = 0;
  }

  return true;
}

Tile Map::getTile(int y, int x) {
  return grid[y][x];
}

void Map::eatPellet(int y, int x) {
  if (grid[y][x] == PELLET) grid[y][x] = EMPTY;
}


void Map::render(SDL_Renderer* renderer) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      SDL_Rect rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE}; 
      if (grid[y][x] == WALL) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
      } else if (grid[y][x] == PELLET) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect pellet = {x * TILE_SIZE + TILE_SIZE/3, y * TILE_SIZE + TILE_SIZE/3, TILE_SIZE/3, TILE_SIZE/3};
        SDL_RenderFillRect(renderer, &pellet);
      }
    }
  }
}
