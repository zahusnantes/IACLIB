#ifndef INFERENCE_H
#define INFERENCE_H

#include "../inc/tools.h"
#include "../inc/images.h"
#include "../inc/conv.h"
#include "../inc/pooling.h"
#include "../inc/fc.h"

void inference(CNN *cnn, DATA3D *input_matrix, DATA3D *kernel, DATA2D *weight_matrix, DATA1D *biases);

#endif