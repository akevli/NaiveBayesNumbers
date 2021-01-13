// Copyright (c) 2020 [Alexander Li]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <bayes/classifier.h>
#include <bayes/model.h>
#include <bayes/image.h>

TEST_CASE("Test Valid Training Files", "[valid-files]") {
  char* image_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\trainingimages");
  char* label_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\traininglabels");
  char* model_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\modelfile");

  REQUIRE(bayes::Train(image_file, label_file, model_file) == 5);
}

TEST_CASE("Test Valid Classifying Files", "[valid-files]") {
  char* image_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\trainingimages");
  char* label_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\traininglabels");
  char* model_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\modelfile");

  REQUIRE(bayes::Classify(image_file, label_file, model_file) == 5);
}

TEST_CASE("Test Invalid Image File Training", "[invalid-files]") {
  char* image_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\fakefile");
  char* label_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\testlabels");
  char* model_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\modelfile");

  REQUIRE(bayes::Classify(image_file, label_file, model_file) == -1);
}

TEST_CASE("Test Invalid Labels File Training", "[invalid-files]") {
  char* image_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\trainingimages");
  char* label_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\fakefile");
  char* model_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\modelfile");

  REQUIRE(bayes::Classify(image_file, label_file, model_file) == -1);
}

TEST_CASE("Test Invalid Image File Classify", "[invalid-files]") {
  char* image_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\fakefile");
  char* label_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\testlabels");
  char* model_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\modelfile");

  REQUIRE(bayes::Classify(image_file, label_file, model_file) == -1);
}

TEST_CASE("Test Invalid Labels File Classify", "[invalid-files]") {
  char* image_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\testimages");
  char* label_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\fakefile");
  char* model_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\modelfile");

  REQUIRE(bayes::Classify(image_file, label_file, model_file) == -1);
}

TEST_CASE("Test Invalid Model File Classify", "[invalid-files]") {
  char* image_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\testimages");
  char* label_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\testlabels");
  char* model_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\fakefile");

  REQUIRE(bayes::Classify(image_file, label_file, model_file) == -3);
}

TEST_CASE("Test Pixel Shade", "[variables]") {
  char* image_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\trainingimages");
  char* label_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\traininglabels");
  char* model_file("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\modelfile");
  bayes::Image image;
  bayes::Classify(image_file, label_file, model_file);
  REQUIRE(image.GetShade(0, 0) == 0);
}

TEST_CASE("Test Total Number of Images", "[variables]") {
  char* image("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\trainingimages");
  char* label("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\traininglabels");
  char* model("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\modelfile");

  bayes::Classifier classifier;
  bayes::Image single_image;
  int image_class;

  std::ifstream model_file(model);
  std::ifstream image_file(image);
  std::ifstream label_file(label);

  classifier.ReadModel(model_file);

  // If the file is not at the end
  while (!image_file.eof() && !label_file.eof()) {

    label_file >> image_class;
    image_file >> single_image; // >> overload to read one image file

    classifier.ClassifyImage(single_image, image_class);
    classifier.class_count_[image_class]++;
    classifier.total_training_samples_++;
  }

  REQUIRE(classifier.total_training_samples_ == 5001);
}

TEST_CASE("Test Total Number of Class Classifications", "[variables]") {
  char* image("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\trainingimages");
  char* label("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\traininglabels");
  char* model("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\modelfile");

  bayes::Classifier classifier;
  bayes::Image single_image;
  int image_class;

  std::ifstream model_file(model);
  std::ifstream image_file(image);
  std::ifstream label_file(label);

  classifier.ReadModel(model_file);

  // If the file is not at the end
  while (!image_file.eof() && !label_file.eof()) {

    label_file >> image_class;
    image_file >> single_image; // >> overload to read one image file

    classifier.ClassifyImage(single_image, image_class);
    classifier.class_count_[image_class]++;
    classifier.total_training_samples_++;
  }

  REQUIRE(classifier.class_count_[0] == 479);
}

TEST_CASE("Test Total Number of Correct Classifications", "[variables]") {
  char* image("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\trainingimages");
  char* label("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\traininglabels");
  char* model("C:\\Users\\Natsu\\CLionProjects\\naive-bayes-akevli\\data\\modelfile");

  bayes::Classifier classifier;
  bayes::Image single_image;
  int image_class;

  std::ifstream model_file(model);
  std::ifstream image_file(image);
  std::ifstream label_file(label);

  classifier.ReadModel(model_file);

  // If the file is not at the end
  while (!image_file.eof() && !label_file.eof()) {
    label_file >> image_class;
    image_file >> single_image;  // >> overload to read one image file

    classifier.ClassifyImage(single_image, image_class);
    classifier.class_count_[image_class]++;
    classifier.total_training_samples_++;
  }

  REQUIRE(classifier.total_correct_ == 4210);
}