// Copyright (c) 2020 [Alexander Li]. All rights reserved.

#ifndef BAYES_MODEL_H_
#define BAYES_MODEL_H_

#include "image.h"

#include <cstdlib>

namespace bayes {

// Classifies the images using the trained model file
int Classify(char *image, char *label, char *model);

// Trains and exports a model file from the given image and label file
int Train(char *image, char *label, char *model);

}  // namespace bayes

#endif  // BAYES_MODEL_H_
