#ifndef FC_H
#define FC_H

#include "tools.h"

#ifdef __cplusplus
extern "C" {
#endif

bool fc(Layer *fc_layer, DATA3D *input_data, DATA3D *output_data);

#ifdef __cplusplus
}
#endif

#endif