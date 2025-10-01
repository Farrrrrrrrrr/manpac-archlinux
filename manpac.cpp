#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PACMAN_SIZE = 50;
const int SPEED = 5;
const int TILE_SIZE = 40;



std::vector<std::string> maze = {
  "####################",
  "#........#.........#",
  "#.####.#.#.#######.#",
  "#.#  #.#.#.#     #.#",
  "#.#  #.#.#.# ### #.#",
  "#.####.###.# # # #.#",
  "#...........# # #..#",
  "####################"
};

int main(int arg, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    return 1;
  }
  SDL_Window* window = SDL_CreateWindow("ManPac: The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  
  if(!window) {
    std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
    return 1;
  }
  
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(!renderer) {
    std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  bool quit = false;
  SDL_Event e;

  int pacmanX = TILE_SIZE;
  int pacmanY = TILE_SIZE;


  while(!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT)  quit = true;
      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) quit = true;
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    int newX = pacmanX;
    int newY = pacmanY;

    if (state[SDL_SCANCODE_UP]) pacmanY -= SPEED;
    if (state[SDL_SCANCODE_DOWN]) pacmanY += SPEED;
    if (state[SDL_SCANCODE_LEFT]) pacmanX -= SPEED;
    if (state[SDL_SCANCODE_RIGHT]) pacmanX += SPEED;

    int gridX = (newX + PACMAN_SIZE / 2) / TILE_SIZE;
    int gridY = (newY + PACMAN_SIZE / 2) / TILE_SIZE;

    if(maze[gridY][gridX] == '#') {
        newX = pacmanX;
        newY = pacmanY;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int y = 0; y < maze.size(); y++) {
      for (int x = 0; x < maze[y].size(); x++) {
        if (maze[y][x] == '#') {
          SDL_Rect tileRect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

          SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
          SDL_RenderFillRect(renderer, &tileRect);

        }else if (maze[y][x] == '.') {
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

          SDL_Rect pellet = {x * TILE_SIZE + TILE_SIZE / 2 - 3, y*TILE_SIZE + TILE_SIZE/2 - 3, 6, 6 };
          SDL_RenderFillRect(renderer, &pellet);

        } 
      }
    }

    SDL_Rect pacman = {pacmanX, pacmanY, PACMAN_SIZE, PACMAN_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &pacman);

    SDL_RenderPresent(renderer);

    SDL_Delay(16);

  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;


}
