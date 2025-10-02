#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

class Maze {
  private:
    std::vector<std::vector<char>> maze;
    std::vector<std::vector<char>> initialMaze;

  public:
    Maze();
    void draw(int playerX, int playerY);
    bool isWall(int x, int y);
    bool isPellet(int x, int y);
    void eatPellet(int x, int y);
    int countPellets();
    void reset();
};

#endif // MAZE_H

