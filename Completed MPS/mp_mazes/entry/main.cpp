#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze maze;
    maze.makeMaze(3, 3);
    cs225::PNG *res = maze.drawMazeWithSolution();
    // auto i = maze.solveMaze(); 
    
    res->writeToFile("./okay.png");
    return 0;
}
