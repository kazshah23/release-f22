#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  done = true; 
}
ImageTraversal::Iterator::Iterator(ImageTraversal* traverse, Point& start, PNG png, double tolerance) {
  /** @todo [Part 1] */
  traverse_ = traverse;
  // curr_point = start;
  curr_point = traverse_ -> peek();
  done = false;
  png_ = png;
  tolerance_ = tolerance;
  start_point = start;
  
}



/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  // 1. Pop
  Point tmp_point = traverse_ -> pop();
  traverse_->visit(tmp_point);
   // 2. Handle Neighbors
  // currPixel = png_.getPixel(tmp_point.x, tmp_point.y);


  CheckFourDirections(tmp_point);
  // 3. Clean the queue/stack (Pop all the visited points in the queue/stack while its not empty)
  while (!(traverse_ -> empty()) && traverse_ -> check(traverse_ -> peek())) {
    traverse_ -> pop();
  }
  if (!(traverse_ -> empty())) {
    curr_point = traverse_ -> peek();
  } else {
    done = true;
  }

  return *this;
}

void ImageTraversal::Iterator::CheckFourDirections(Point tmp_point) {
  int width = png_.width();
  int height = png_.height();
  int x = tmp_point.x;
  int y = tmp_point.y; 

  HSLAPixel & startPixel = png_.getPixel(start_point.x, start_point.y);
  
  // right bound
  if (x + 1 < width && traverse_->check(Point(x+1,y)) == false) {
    Point right(x + 1, y);
    HSLAPixel& currPixel = png_.getPixel(tmp_point.x + 1, tmp_point.y); 
    if (calculateDelta(startPixel, currPixel) < tolerance_) {
      traverse_ -> add(right);
    }
  } 
  // bottom bound
  if (y + 1 < height && traverse_->check(Point(x,y+1)) == false) {
    Point bottom(x, y + 1);
    HSLAPixel& currPixel = png_.getPixel(tmp_point.x, tmp_point.y + 1);
    if (calculateDelta(startPixel, currPixel) < tolerance_) {
      traverse_ -> add(bottom);
    }

  }
  // left bound
  if (x - 1 >= 0 && traverse_->check(Point(x-1,y)) == false) {
    Point left(x - 1, y);
    HSLAPixel& currPixel = png_.getPixel(tmp_point.x - 1, tmp_point.y);
    if (calculateDelta(startPixel, currPixel) < tolerance_) {
      traverse_ -> add(left);
    }
  }
  // upper bound
  if (y - 1 >= 0 && traverse_->check(Point(x,y-1)) == false) {
    Point up(x, y - 1);
    HSLAPixel& currPixel = png_.getPixel(tmp_point.x, tmp_point.y - 1);
    if (calculateDelta(startPixel, currPixel) < tolerance_) {
      traverse_ -> add(up);
    }
  }
}


/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_point;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  // /** @todo [Part 1] */
  // if (iterate == nullptr && other.iterate == nullptr) return false;
  if (done == other.done) {
    return false; 
  } 
  return true;  

}

bool ImageTraversal::Iterator::visitable(Point point) {
  if (point.x >= png_.width() || point.y >= png_.height()) return false;
  return true;
  // HSLAPixel pt1 = *(png_.getPixel(point.x, point.y));
}