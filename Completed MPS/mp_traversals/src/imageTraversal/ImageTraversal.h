/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"
#include <vector>

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator();
    Iterator(ImageTraversal* traverse, Point& start, PNG png, double tolerance);

    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);
    bool visitable(Point point);
    void helper(HSLAPixel pixel);
    void CheckFourDirections(Point);
  

    /** @todo [Part 1] */
    /** add member functions if neccesary*/


  private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/
    ImageTraversal* traverse_;
    Point curr_point;
    Point start_point;
    double tolerance_;
    bool done;
    PNG png_;


    

  };

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point & t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point peek() const = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;

  virtual void visit(Point curr_point) = 0;
  virtual bool check(Point curr_point) = 0;



  virtual PNG get_png() = 0;
public: 
   
private:
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  


};
