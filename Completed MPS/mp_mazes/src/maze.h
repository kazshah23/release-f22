/* Your code here! */
#include "dsets.h"
#include "cs225/PNG.h"
#include <iostream>
#include <vector>


class SquareMaze {
  public:
    SquareMaze();
    void makeMaze(int, int);
    bool canTravel(int, int, int) const;
    void setWall (int, int, int, bool);
    std::vector <int> solveMaze();
    cs225::PNG* drawMaze() const;
    cs225::PNG* drawMazeWithSolution();

  private:
    int width, height;
    std::vector<std::pair<bool, bool>> walls; // right, down
    DisjointSets dsets;
};
