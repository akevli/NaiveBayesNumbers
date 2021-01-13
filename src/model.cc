// Copyright 2020 [Alexander Li]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/model.h>

#include <iostream>

namespace bayes {

int Classify(char* image, char* label, char* model) {

  bayes::Classifier classifier;
  bayes::Image single_image;
  int class_number;

  std::ifstream model_file(model);
  if (!model_file) {
    std::cout << "Error opening model file" << std::endl;
    return -3;
  }

  // Check if the files are valid
  if (!classifier.isValidFile(image, label)) {
    return -1;
  }
  std::ifstream image_file(image);
  std::ifstream label_file(label);

  classifier.ReadModel(model_file);

  // If the file is not at the end
  while (!label_file.eof()) {

    label_file >> class_number;
    image_file >> single_image; // >> overload to read one image file

    classifier.class_count_[class_number]++;
    classifier.total_training_samples_++;
    classifier.ClassifyImage(single_image, class_number);
  }
  classifier.PrintResults();
  return 5;
}

int Train(char* image, char* label, char* model) {

  bayes::Classifier classifier;
  bayes::Image single_image;
  int class_number;

  // Check if the files are valid
  if (!classifier.isValidFile(image, label)) {
    return -1;
  }
  std::ifstream image_file(image);
  std::ifstream label_file(label);
  std::ofstream model_file(model);

  // If the file is not at the end
  while (!label_file.eof()) {

    label_file >> class_number;
    image_file >> single_image; // >> overload to read one image file

    classifier.total_training_samples_++;
    classifier.class_count_[class_number]++;
    classifier.AddSuccesses(single_image, class_number);
  }

  // Create a new file and write the model into it
  classifier.ExportModel(model_file);
  return 5;
}
}  // namespace bayes
