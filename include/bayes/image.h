// Copyright (c) 2020 [Alexander Li]. All rights reserved.

#ifndef BAYES_IMAGE_H_
#define BAYES_IMAGE_H_

#include <cstdlib>
#include <fstream>

namespace bayes {

// The max height and width of the image size.
constexpr size_t kImageSize = 28;

// 0-9 inclusive.
constexpr size_t kNumClasses = 10;

// Shaded or not shaded.
constexpr size_t kNumShades = 2;

class Image {
 protected:
  // The pixels of an image (shaded  = 1 and not shaded = 0)
  int pixels_[kImageSize][kImageSize]{};

  // Operator Overload to convert image file into binary
  friend std::ifstream &operator >> (std::ifstream &in, Image &image);

 public:
  // Getter for the pixel at the given row and column
  int GetShade(int row, int col);
};

}  // namespace bayes

#endif  // BAYES_IMAGE_H_
