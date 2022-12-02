#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  png_ = png;
  start_point_ = start;
  tolerance_ = tolerance;
  queue_.push(start);

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
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
 // BFS* it = new BFS(png_, start_point_, tolerance_);
  return ImageTraversal::Iterator(this, start_point_, png_, tolerance_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  queue_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point output = queue_.front();
  queue_.pop();
  return output;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return queue_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
   return queue_.empty();
}
PNG BFS::get_png() {
  return png_;
}

void BFS::visit(Point curr_point) {
  visited_[curr_point.x][curr_point.y] = true;
}

bool BFS::check(Point curr_point) {
  return visited_[curr_point.x][curr_point.y];
}