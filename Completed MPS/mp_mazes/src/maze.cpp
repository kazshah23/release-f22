/* Your code here! */
  #include "maze.h"
  #include <queue>
  #include <map>
  #include <algorithm>
  #include <iostream>
  using namespace std;

  SquareMaze::SquareMaze() {


  }
  void SquareMaze::makeMaze(int width, int height) {
    // Set parameters and sets
    this -> width = width;
    this -> height = height;
    dsets.addelements(width * height);

    // Construct a maze with all the walls in place
    for (int i = 0; i < (width * height); i++) {
		  walls.push_back(std::pair<bool, bool>(true, true));
	  }
    
    // Randomly select walls to delete
      // Check if the wall is on the perimeter of the maze
      // Check for cycle (use disjoint sets)
      // If none of the above conditions is violated, delete the wall
      // Repeat until every cell is connected to the maze
    while (dsets.size(0) != width * height) {
      int cell1 = rand() % ((width * height) - 1); // picks a random cell 
      int x1 = cell1 % width; // x coordinate for the 1d vector
      int y1 = (cell1 - x1) / width; // y coordinate for the 1d vector
      int wallone = rand() % 2; // 0 for right 1 for down
      int x2 = x1; // initalize 
      int y2 = y1; // intialize

      if (wallone == 0) { // if we choose right wall 
        x2 += 1; // then go right 
      } else { // if we choose down wall
        y2 += 1; // go down
      }

      int cell2 = (y2 * width) + x2; // creates second cell 
      if (x2 >= width || y2 >= height) continue; // out of bounds check 
      if (dsets.find(cell1) == dsets.find(cell2)) continue; // out of bounds check
      
      if (wallone == 0) walls[cell1].first = false; // if right, set the first index in pair (right) to false
      else walls[cell1].second = false; // if down, set the second index in pair (down) to false
      dsets.setunion(cell1, cell2); // combine sets to avoid cycling
    }

  }
  /*
  . . .
  . . .
  . . .

  */
  bool SquareMaze::canTravel(int x, int y, int dir) const {
    bool output = true;
    if (dir == 1 && y >= height) return false;
    if (dir == 3 && y <= 0) return false; 
    if (dir == 0) output = walls[x + y * width].first;
    else if (dir == 1) output = walls[x + y * width].second;
    else if (dir == 2 && x > 0) output = walls[x - 1 + y * width].first;
    else if (dir == 3 && y > 0) output = walls[x + (y-1) * width].second;
    return !output;
  }
  void SquareMaze::setWall (int x, int y, int dir, bool exists) {
    if (dir == 0) walls[x + y * width].first = exists;
    else if (dir == 1) walls[x + y * width].second = exists;
  }

  std::vector<int> SquareMaze::solveMaze() {
    std::queue<int> que;
    std::vector<bool> visited;
    std::vector<int> vLen;
    std::map<int, int> path;
    
    for (int i = 0; i < (height * width); i++) {
      vLen.push_back(-1);
      visited.push_back(false);
    }

    int length = 0;
    que.push(0);
    // BFS Traversal
    while (!que.empty()) {
      int front = que.front();
      visited[front] = true; // mark true so we dont visit again 
      int currlen = vLen[front]; // length of the cell we are at 
      int newlen = currlen + 1; // length of the cells that we are gonna change
      que.pop();
      int coord = front % width; // To get the coordinate 
      int ycoord = front / width;
      if (canTravel(coord, ycoord, 0)) { // make sure its not out of bounds 
        if (front + 1 < int(visited.size())) {
          if (!visited[front + 1]) { // make sure its not visited yet 
            path.insert(std::pair<int,int>(front + 1, front)); // map to show where we went next 
            que.push(front + 1); // add to the queue to keep traversal going since its valid 
            vLen[front + 1] = newlen; // change the lengths at that point
          }
        }
      }
      // Repeat for other 3 directions
      if (canTravel(coord, (ycoord), 1)) { 
        if (front + width < int(visited.size())) {
          if (!visited[front + width]) {
            path.insert(std::pair<int,int>(front + width, front));
            que.push(front + width);
            vLen[front + width] = newlen;
          }
        }
      }
      if (canTravel(coord, ycoord, 2)) { 
        if (front - 1 >= 0) {
          if (!visited[front - 1]) {
            path.insert(std::pair<int,int>(front - 1, front));
            que.push(front - 1);
            vLen[front - 1] = newlen;
          }
        }
      }
      if (canTravel(coord, ycoord, 3)) { 
        if (front - width >= 0) {
          if (!visited[front - width]) {
            path.insert(std::pair<int,int>(front - width, front));
            que.push(front - width);
            vLen[front - width] = newlen;
          }
        }
      }
      length++; // increment length
     }
    for (int i = 0; i < width * height; i++){
      auto it = path.find(i);
      if (it != path.end() ){
        int prev = path[i];
        // std::cout<< "x: " << i % width << " y:" << i/width << " prev: " << "p_x: " << prev % width << " p_y:" << prev/width<<std::endl;
      }
    }
    // find longest Index 
    int longestIndex = -100;
    int lowestX = 10000;
    for (int i = width * height - 1; i > (width*(height-1)); i--) {
      if (vLen[i] > longestIndex && (i % width < lowestX)) longestIndex = i;
    }
    std::vector<int> directions;
    
    // std::cout << "Longest index: " << longestIndex << std::endl;
    
    int amount_iteration = vLen[longestIndex];
    while (true) {
      int prev = path[longestIndex];
      if (longestIndex == prev + 1) directions.push_back(0);
      if (longestIndex == prev + width) directions.push_back(1);
      if (longestIndex == prev - 1) directions.push_back(2);
      if (longestIndex == prev - width) directions.push_back(3);
      longestIndex = prev;
      if (prev == 0) break;
    }
    std::reverse(directions.begin(), directions.end());
    // for (size_t i = 0; i < directions.size(); i++) std::cout << directions[i] << std::endl;
    return directions;
/*
    // // Find the index at the bottom row with the largest length
    // int longestIndex = -100;
    // int lowestX = 10000;
    // for (int i = width * (height - 1); i < (width*height); i++) {
    //   if (vLen[i] > longestIndex && (i % width < lowestX)) longestIndex = vLen[i];
    // }
    // // Find the path to that index using the map we made above
    // std::cout << longestIndex << std::endl;
    // return {longestIndex};
    // std::vector<int> pathIndexes;
    // while (longestIndex != 0) {
    //   pathIndexes.push_back(longestIndex);
    //   longestIndex = path[longestIndex];
    // }
    // pathIndexes.push_back(0);
    // for (size_t i = 0; i < pathIndexes.size(); i++) { 
    //   std::cout << "<" << pathIndexes[i] << ">" << std::endl;
    // }
    // // Reverse vector
    // std::reverse(pathIndexes.begin(), pathIndexes.end());
    // Now detect if a right left up or down movement is made with the vector of indexes
    // std::vector<int> output;
    // for (size_t i = 0; i < pathIndexes.size() - 1; i++) {
    //   if (pathIndexes[i] + 1 == pathIndexes[i + 1]) output.push_back(0);
    //   else if (pathIndexes[i] + width == pathIndexes[i + 1]) output.push_back(1);
    //   else if (pathIndexes[i] - 1 == pathIndexes[i + 1]) output.push_back(2);
    //   else if (pathIndexes[i] - width == pathIndexes[i + 1]) output.push_back(3);
    // }
  */
  }
  // Create a new PNG and set dimensions (DONE)
  // Blacken the topmost row (DONE)
  // Blacken the leftmost column (DONE)
  // Iterate throw width and column
    // If right wall exists blacken 
    // If bottom wall exists blacken

  cs225::PNG* SquareMaze::drawMaze() const {
    cs225::PNG* output = new cs225::PNG(width*10+1, height*10+1);

    for (int i = 10; i < width*10+1; i++) {
      cs225::HSLAPixel& pix = output -> getPixel(i, 0);
      pix.l = 0.0;
    }
    for (int i = 0; i < height*10+1; i++) {
      cs225::HSLAPixel& pix = output -> getPixel(0, i);
      pix.l = 0.0;
    }

    for (int i = 0; i < width; i++) {
      for (int j = 0; j <height; j++) {
        for (int k = 0; k < 11; k++) {
          if (walls[i + j * width].first) {
            cs225::HSLAPixel& p = output -> getPixel(10 * i + 10, 10 * j + k);
            p.l = 0.0;
          } 
          if (walls[i + j * width].second) {
            cs225::HSLAPixel& p = output -> getPixel(10 * i + k, 10 * j + 10);
            p.l = 0.0;
          }
        }
      }
    }

    return output;
  }
  cs225::PNG* SquareMaze::drawMazeWithSolution() {
    cs225::PNG* output = drawMaze();
    std::vector<int> path = solveMaze();
    int x = 5;
    int y = 5;

    for (size_t i = 0; i < path.size(); i++) {
      if (path[i] == 0) {
        for (int j = 0; j < 10; j++) {
          cs225::HSLAPixel& curr = output ->getPixel(x,y);
          curr.h = 0.0; 
          curr.s = 1.0;
          curr.l = 0.5;  
          x+=1;
        }
      }
      else if (path[i] == 1) {
        for (int j = 0; j < 10; j++) {
          cs225::HSLAPixel& curr = output ->getPixel(x,y);
          curr.h = 0.0; 
          curr.s = 1.0;
          curr.l = 0.5; 
          y+=1;
        }
      }
      else if (path[i] == 2) {
        for (int j = 0; j < 10; j++) {
          cs225::HSLAPixel& curr = output ->getPixel(x,y);
          curr.h = 0.0; 
          curr.s = 1.0;
          curr.l = 0.5; 
          x-=1;
        }
      }
      else if (path[i] == 3) {
        for (int j = 0; j < 10; j++) {
          cs225::HSLAPixel& curr = output ->getPixel(x,y);
          curr.h = 0.0; 
          curr.s = 1.0;
          curr.l = 0.5; 
          y-=1;
        }
      }
    }
    cout << x << ", " << y << endl;
    cs225::HSLAPixel & cur_pixel = output->getPixel(x, y);
    for (int k = 1; k <= 9; k++) {
        cs225::HSLAPixel& curr = output -> getPixel(x -5 + k, y + 5);
        curr.l = 1.0;
    }
    return output;
  }
