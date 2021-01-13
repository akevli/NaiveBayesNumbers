// Copyright (c) 2020 [Alexander Li]. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_

#include "image.h"
#include "model.h"

namespace bayes {

// The user-define kValue for Laplace Smoothing
const double kValue = 0.5;

class Classifier {
 protected:
  // The number of correct classifications for each class
  int correct_by_class_[bayes::kNumClasses];

  // The independent probability of each class
  double prob_by_class_[bayes::kNumClasses];

  // The individual probabilities for each pixel for each class for
  // whether it's shaded or not.
  //
  // Examples:
  // probs[2][10][7][0] is the computed probability that a pixel at
  // [2][10] for class 7 is not shaded.
  //
  // probs[0][0][0][1] is the computed probability that a pixel at
  // [0][0] for class 0 is shaded.
  double probs_[kImageSize][kImageSize][kNumClasses][kNumShades];

 public:
  // Constructor to initialize values
  Classifier();

  // Total number of each class
  int class_count_[bayes::kNumClasses];

  // The total number of correct classifications
  int total_correct_;

  // Total number of training samples
  int total_training_samples_;

  // Checks if the image and label files are valid
  bool isValidFile(char* image, char* label);

  // Reads the model file
  void ReadModel(std::ifstream &file);

  // Classifies the image
  void ClassifyImage(Image &image, int image_class);

  // Prints the results of the classification
  void PrintResults();

  // Adds the number of successes for each identified shade
  void AddSuccesses(Image &image, int image_class);

  // Exports the model file
  void ExportModel(std::ofstream &of);
};

}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

