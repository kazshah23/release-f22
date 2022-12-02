/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */
#include "cs225/PNG.h"
#include <vector>

class Image : public cs225::PNG {
  public:
  Image();
  void lighten();
  void lighten(double amount);
  void darken();
  void darken(double amount);
  void saturate();
  void saturate(double amount);
  void desaturate();
  void desaturate(double amount);
  void grayscale();
  void rotateColor(double degrees);
  void illinify();
  void scale(double factor);
  void scale(unsigned w, unsigned h);

  private:
  std::vector<std::vector<int>> pixels;

};

#pragma once