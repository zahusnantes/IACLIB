#ifndef CONV_H
#define CONV_H

#include "tools.h"

#ifdef __cplusplus
extern "C" {
#endif

bool conv(Layer *conv_layer, DATA3D *input_data, DATA3D *kernel, DATA3D *output_data);

#ifdef __cplusplus
}
#endif

#endif