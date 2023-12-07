#ifndef POOL_H
#define POOL_H

#include "tools.h"

bool pooling(Layer *pooling_layer, DATA3D *input_data, DATA3D *output_data);
void max_pooling(Layer *pooling_layer, DATA3D *input_data, DATA3D *output_data);
void avg_pooling(Layer *pooling_layer, DATA3D *input_data, DATA3D *output_data);
void min_pooling(Layer *pooling_layer, DATA3D *input_data, DATA3D *output_data);

#endif