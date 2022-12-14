/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void mark_visited(Point curr_point);
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

  void visit(Point curr_point);
  bool check(Point curr_point);
  PNG get_png();

private:
  /** @todo [Part 1] */
  /** add private members here*/
  // std::vector<std::vector<bool>> visited_;
  PNG png_;
  Point start_point_;
  double tolerance_;
  std::queue<Point> queue_;
  std::vector<std::vector<bool>> visited_;

};
