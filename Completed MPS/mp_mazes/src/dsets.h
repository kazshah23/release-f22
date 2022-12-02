/* Your code here! */
#pragma once 
#include <vector>

class DisjointSets {
  public:
    void addelements(int);
    int find(int);
    void setunion(int a, int b); 
    int size(int elem); 

  private:
    std::vector<int> elements_; 

};