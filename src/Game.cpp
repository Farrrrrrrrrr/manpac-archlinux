#include "Game.h"
#include <iostream>

Game::Game() : score(0), lives(3), running(false) {}



bool Game::init(const char* title, int width, int height) {
  // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }
    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    font = TTF_OpenFont("assets/FreeSans.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }
   
    // Load Pacman texture
    SDL_Surface* surface = SDL_LoadBMP("assets/pacman.bmp");
    if (!surface) {
        std::cerr << "Pacman image not found, falling back intro yellow box. \n";
        pacTexture = nullptr; // Use nullptr to indicate no texture"
    } else {
        pacTexture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);

        if (!pacTexture) {
            std::cerr << "Unable to create texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }
    }



    // Load map
    map.load("assets/map1.txt");
    pacman.setPosition(1, 1); // Starting position
    
    running = true;

    return true;
}

void Game::run() {
  while (running) {
    processInput();
    update();
    render();
    SDL_Delay(100);

  }
}

void Game::cleanup() {
  if (pacTexture) {
    SDL_DestroyTexture(pacTexture);
    pacTexture = nullptr;
  }
  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  TTF_Quit();

}

void Game::processInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) running = false;
    pacman.handleInput(event, map);
  }
}

void Game::update() {
  if (map.getTile(pacman.getY(), pacman.getX()) == PELLET) {
    score+= 10;

    map.eatPellet(pacman.getY(), pacman.getX());
  }
    std::cout << "Score: " << score << "  Lives:  " << std::endl;
  
  
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  map.render(renderer);
  pacman.render(renderer, pacTexture);

  // draw HUD text with SDL_ttf (Score+ lives)
  
  SDL_RenderPresent(renderer);
}

