// Copyright 2020 [Alexander Li]. All rights reserved.

#include <bayes/image.h>

#include <string>

namespace bayes {

int Image::GetShade(int row, int col) {
  if (pixels_[row][col] == 0) {
    return 0; // white (not shaded)
  } else {
    return 1; // gray or black (shaded)
  }
}

std::ifstream& operator >> (std::ifstream &file, Image &image) {
  std::string row;
  for (auto &pixel : image.pixels_) {
    // Checks if the next row is the end of the file
    if (!std::getline(file, row)) {
      return file;
    }

    for (size_t character = 0; character < kImageSize; ++character) {
      if (row[character] == '+' || row[character] == '#') {  // '+' and '#' = 1
        pixel[character] = 1;
      } else if (row[character] == ' ') { // ' ' = 0
        pixel[character] = 0;
      }
    }
  }

  return file;
}
}  // namespace bayes

