// Copyright (c) 2020 [Alexander Li]. All rights reserved.

#include <bayes/model.h>

#include <string>

int main(int argc, char *argv[]) {
  // If the command-line indicates classify
  if (strcmp(argv[1], "-classify") == 0) {
    return bayes::Classify(argv[2], argv[3], argv[4]);
  }

  // If the command-line indicates -train
  if (strcmp(argv[1], "-train") == 0) {
    return bayes::Train(argv[2], argv[3], argv[4]);
  }

}