// Copyright 2020 [Alexander Li]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>

#include <iostream>

namespace bayes {

Classifier::Classifier() {
  total_training_samples_ = 0;
  total_correct_ = 0;
  for (size_t i = 0; i < kNumClasses; ++i) {
    correct_by_class_[i] = 0;
    class_count_[i] = 0;
  }

  // Loops through all the probabilities and initializes it to 0.
  for (size_t row = 0; row < kImageSize; ++row) {
    for (size_t column = 0; column < kImageSize; ++column) {
      for (size_t image_class = 0; image_class < kNumClasses; ++image_class) {
        for (size_t shade = 0; shade < kNumShades; ++shade) {
          probs_[row][column][image_class][shade] = 0;
        }
      }
    }
  }
}

bool Classifier::isValidFile(char* image, char* label) {
  std::ifstream image_file(image);
  std::ifstream label_file(label);
  if (!image_file) {
    std::cout << "Error opening image file" << image << std::endl;
    return false;
  }
  if (!label_file) {
    std::cout << "Error opening label file" << label << std::endl;
    return false;
  }
  return true;
}

void Classifier::AddSuccesses(Image &image, int image_class) {
  // Add to total number of times Fij = f when class = c
  for (size_t row = 0; row < kImageSize; ++row) {
    for (size_t column = 0; column < kImageSize; ++column) {
      probs_[row][column][image_class][image.GetShade(row, column)]++;
    }
  }
}

void Classifier::ReadModel(std::ifstream &file) {
  // Read the probabilities of each class
  for (double &probability_of_class : prob_by_class_) {
    file >> probability_of_class;
  }

  // Read the probabilities for each character
  for (size_t row = 0; row < kImageSize; ++row) {
    for (size_t column = 0; column < kImageSize; ++column) {
      for (size_t image_class = 0; image_class < kNumClasses; ++image_class) {
        for (size_t shade = 0; shade < kNumShades; ++shade) {
          file >> probs_[row][column][image_class][shade];
        }
      }
    }
  }
}

void Classifier::ExportModel(std::ofstream &of) {
  // Print the calculation of priors / class probabilities
  for (int number_of_correct_class : class_count_) {
    of << (double) number_of_correct_class / total_training_samples_ << std::endl;
  }

  for (size_t row = 0; row < kImageSize; ++row) {
    for (size_t column = 0; column < kImageSize; ++column) {
      for (size_t image_class = 0; image_class < kNumClasses; ++image_class) {
        for (size_t shade = 0; shade < kNumShades; ++shade) {
          // Laplace Smoothing Formula
          probs_[row][column][image_class][shade] =
              (kValue + probs_[row][column][image_class][shade])
              / ((2 * kValue) + class_count_[image_class]);
          // Print probabilities
          of << probs_[row][column][image_class][shade] << std::endl;
        }
      }
    }
  }
}

void Classifier::ClassifyImage(Image &image, int image_class) {
  int predicted_class = 0;
  double temp_prob = -999999999; // Initial posterior probability

  for (size_t class_number = 0; class_number < kNumClasses; ++class_number) {
    double posterior_prob = log(prob_by_class_[class_number]);

    for (size_t row = 0; row < kImageSize; ++row) {
      for (size_t column = 0; column < kImageSize; ++column) {
        posterior_prob += log(probs_[row][column][class_number][image.GetShade(row, column)]);
      }
    }

    // Setting the predicted class to the highest posterior probability
    if (temp_prob < posterior_prob) {
      predicted_class = class_number;
      temp_prob = posterior_prob;
    }
  }

  if (image_class == predicted_class) {
    total_correct_++;
    correct_by_class_[image_class]++;
  }
}

void Classifier::PrintResults() {
  // Print results for each class
  for (size_t class_number = 0; class_number < kNumClasses; ++class_number) {
    std::cout << "Class: " << class_number << " - Percentage Correct: "
              << (100 * correct_by_class_[class_number]) /
              class_count_[class_number]
              << "%" << std::endl;
  }

  // Print results for the overall classification
  std::cout << "Overall Percentage Correct: "
            << (100 * total_correct_) / total_training_samples_ << "%"
            << std::endl;
}
}  // namespace bayes