#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */

 /**
 * A point must not be visited in a traversal if either of the statements are true 
    The point has already been visited 
    The pixel at the point is greater than or equal to a given tolerance away from the pixel at the starting point 
    Use ImageTraversal::calculateDelta\
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  png_ = png;
  start_point = start;
  tolerance_ = tolerance;
  stack_.push(start);

  visited_.resize(png_.width());
  for(unsigned row = 0; row < visited_.size(); row++) {
    visited_[row].resize(png_.height());
    for (unsigned col = 0; col < visited_[row].size(); col++) {
      visited_[row][col] = false;
    }
  }
  
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, start_point, png_, tolerance_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  stack_.push(point);
}
PNG DFS::get_png() {
  /** @todo [Part 1] */
  return png_;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point output;
  output = stack_.top();
  stack_.pop();
  return output;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return stack_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return stack_.empty();
}

void DFS::visit(Point curr_point) {
  visited_[curr_point.x][curr_point.y] = true;
}

bool DFS::check(Point curr_point) {
  return visited_[curr_point.x][curr_point.y];
}
