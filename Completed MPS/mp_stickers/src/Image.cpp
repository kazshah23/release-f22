#include "Image.h"
using namespace cs225;


Image::Image() {

}
// nearest neighbor algo
void Image::scale(double factor) {
  Image original = *this;
  // "this" is the image that is resized into what we want it to be at
  this -> resize(factor * width(), factor * height());
  // The next step is to obtain the pixels from the original image, and put it on "this" 
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++) {
      this -> getPixel(col,row) = original.getPixel(col / factor, row / factor);
    } 
  }
}
void Image::scale(unsigned w, unsigned h) {
  // Image original = *this;
  // "this" is the image that is resized into what we want it to be at
  // this -> resize(w * width(), h * height());
  // The next step is to obtain the pixels from the original image, and put it on "this" 
  double wFac = (double)w / width();
  double hFac= (double)h / height();

  if (hFac > wFac) {
    scale(wFac);
  } else {
    scale (hFac);
  }
}

void Image::illinify() {
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++){
      HSLAPixel &pixel = this -> getPixel(col, row);
        if (pixel.h >= 114 && pixel.h <= 243) {
          pixel.h = 216; 
        } else {
          pixel.h = 11;
        }
    }
  }
}

void Image::lighten() {
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++){
      HSLAPixel &pixel = this -> getPixel(col, row);
      pixel.l += 0.1;
      if (pixel.l > 1) {
        pixel.l = 1;
      }
    }
  }
}

void Image::lighten(double amount) {
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++){
      HSLAPixel &pixel = this -> getPixel(col, row);
      pixel.l += amount;
      if (pixel.l > 1) {
        pixel.l = 1;
      }
    }
  }
}
 
void Image::darken() {
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++){
      HSLAPixel &pixel = this -> getPixel(col, row);
      pixel.l -= 0.1;
      if (pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}
void Image::darken(double amount) {
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++){
      HSLAPixel &pixel = this -> getPixel(col, row);
      pixel.l -= amount;
      if (pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}

void Image::saturate() {
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++){
      HSLAPixel &pixel = this -> getPixel(col, row);
      pixel.s += 0.1;
      if (pixel.s > 1) {
        pixel.s = 1;
      } 
    }
  }
}

void Image::saturate(double amount) {
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++){
      HSLAPixel &pixel = this -> getPixel(col, row);
      pixel.s += amount;
      if (pixel.s > 1) {
        pixel.s = 1;
      } 
    }
  }
}

void Image::desaturate() {
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++){
      HSLAPixel &pixel = this -> getPixel(col, row);
      pixel.s -= 0.1;
      if (pixel.s < 0) {
        pixel.s = 0;
      } 
    }
  }
}

void Image::desaturate(double amount) {
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++){
      HSLAPixel &pixel = this -> getPixel(col, row);
      pixel.s -= amount;
      if (pixel.s < 0) {
        pixel.s = 0;
      } 
    }
  }
}


void Image::grayscale() {
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++){
      HSLAPixel &pixel = this -> getPixel(col, row);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {
  for (unsigned int row = 0; row < this -> height(); row++) {
    for (unsigned int col = 0; col < this -> width(); col++){
      HSLAPixel &pixel = this -> getPixel(col, row);
      if (degrees > 0) {
        if (pixel.h + degrees <= 360) {
          pixel.h += (degrees);
        } else {
          pixel.h = (pixel.h + degrees) - 360;
        }
      } else {
        if (pixel.h - degrees > 0) {
          pixel.h -= degrees;
        } else {
          pixel.h = (pixel.h - degrees) + 360;
        }
      }
    }
  }
}

