#include "dsets.h"

// Creates n unconnected root nodes at the end of the vector.
void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) elements_.push_back(-1);
}
// This function should compress paths and works as described in lecture.
int DisjointSets::find(int elem) {
  if (elements_[elem] < 0) return elem;
  return find(elements_[elem]);
}

void DisjointSets::setunion(int a, int b) {
  int treeA = find(a);
  int treeB = find(b);
  int newSize = elements_[treeA] + elements_[treeB];
  if (treeA == treeB) return;

  if (elements_[treeA] < elements_[treeB]) {
    elements_[treeB] = treeA;
    elements_[treeA] = newSize;
  } else {
    elements_[treeA] = treeB;
    elements_[treeB] = newSize;
  }
  
}

int DisjointSets::size(int elem) {
  return -(elements_[find(elem)]);
}