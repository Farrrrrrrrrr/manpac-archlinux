#include <iostream>
#include "Maze.h"

Maze::Maze() {
  initialMaze = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
    {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', ' ', '#', 'E', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
  };
  maze = initialMaze;
}

void Maze::draw(int playerX, int playerY) {
  for (int y = 0; y < (int)maze.size(); y++) {
    for (int x = 0; x < (int)maze[y].size(); x++) {
      if (x == playerX && y == playerY)
        std::cout << "P";
      else
        std::cout << maze[y][x];
    }
    std::cout << "\n";
  }
}

bool Maze::isWall(int x, int y) {
  return maze[y][x] == '#';

}

bool Maze::isPellet(int x, int y) {
  return maze[y][x] == '.';

}

void Maze::eatPellet(int x, int y) {
  if (maze[y][x] == '.') {
    maze[y][x] = ' ';
  }
}

int Maze::countPellets() {
  int count = 0;
  for (const auto& row : maze) {
    for (char c : row) {
      if (c == '.') count++;
    }
  }
  
  return count;
}

void Maze::reset() {
  maze = initialMaze;
}
