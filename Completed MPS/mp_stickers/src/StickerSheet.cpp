#include <iostream>
#include "StickerSheet.h"
#include "Image.h"
#include <vector>
using namespace cs225;


StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  sticker_max = max;
  img_ = picture;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
  if (stickers_.size() >= sticker_max) return -1;
  stickers_.push_back(&sticker);
  x_.push_back(x);
  y_.push_back(y);
  size_++;
  return size_ - 1;
}



// 2, 4, 5, 3, 1
//size_ = 5 
// max = 3
void StickerSheet::changeMaxStickers(unsigned max) {
  if (size_ > max) {
    for (unsigned i = 0; i < size_ - max; i++) {
      stickers_.pop_back();
      x_.pop_back();
      y_.pop_back();
    }
    size_ -= (size_ - max);
  } 

  sticker_max = max;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (index < size_) {
    x_[index] = x;
    y_[index] = y;
    return true;
  }
  return false;
}

void StickerSheet::removeSticker(unsigned index) {
  if (index >= stickers_.size()) return;
  this -> stickers_.erase(this -> stickers_.begin() + index);
  this -> x_.erase(this -> x_.begin() + index);
  this -> y_.erase(this -> y_.begin() + index);
  size_--;
}

// 
Image* StickerSheet::getSticker(unsigned index) {
  if (index >= size_) {
    return NULL;
  }
  return stickers_[index];

}
//loop through all the stickers 
    //draw the sticker i
      // loop over all coordinates of sticker i
      // img[x + r][y + c] = sticker[i] (r, c)
      // HSLA& base_image = img.getPixel(x + r, y + c)
      // const HSLA& sticker_pix = sticker[i].getPixel(r, c)
      // base_image = sticker_pix;

Image StickerSheet::render() const {
  Image output(img_);
  for (unsigned i = 0; i < size_; i++) {
    if (stickers_[i] -> width() + x_[i] > output.width()) {
      output.resize(stickers_[i] -> width() + x_[i], output.height());
    }
    if (stickers_[i] -> height() + y_[i] > output.height()) {
      output.resize(output.width(), stickers_[i] -> height() + y_[i]);
    }


    for (unsigned row = 0; row < stickers_[i] -> width(); row++) {
      for (unsigned col = 0; col < stickers_[i] -> height(); col++) {

        HSLAPixel& base_image = output.getPixel(row + x_[i], col + y_[i]);
        const HSLAPixel& sticker_pixel = stickers_[i] -> getPixel(row, col);

        if (sticker_pixel.a > 0) {
          base_image = sticker_pixel;
        }


      }
    }
  }
  return output;
}