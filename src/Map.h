#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>

enum Tile { EMPTY, WALL, PELLET };

class Map {
    public:
    bool load(const std::string& filename);
    void render(SDL_Renderer* renderer);
    Tile getTile(int x, int y);
    void eatPellet(int x, int y);

    int getWidth() const { return width;}
    int getHeight() const { return height;}

    private:
    std::vector<std::vector<Tile>> grid;

    int width = 0, height = 0;

};
