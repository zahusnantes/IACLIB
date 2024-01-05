#ifndef INFERENCE_H
#define INFERENCE_H

#include "../inc/tools.h"
#include "../inc/data.h"
#include "../inc/conv.h"
#include "../inc/pooling.h"
#include "../inc/fc.h"

#ifdef __cplusplus
extern "C" {
#endif

bool inference(CNN *cnn, DATA3D *input_matrix);

#ifdef __cplusplus
}
#endif

#endif