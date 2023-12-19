#ifndef POOL_H
#define POOL_H

#include "tools.h"

#ifdef __cplusplus
extern "C" {
#endif

bool pooling(Layer *pooling_layer, DATA3D *input_data, DATA3D *output_data);

#ifdef __cplusplus
}
#endif

#endif