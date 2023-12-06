#ifndef POOL_H
#define POOL_H

#include "tools.h"

bool pooling(Layer *pooling_layer, DATA1D *input_data, DATA1D *output_data, int input_height, int input_width, int num_channels);
void max_pooling(Layer *pooling_layer, DATA1D *input_data, DATA1D *output_data, int input_height, int input_width, int num_channels);
void avg_pooling(Layer *pooling_layer, DATA1D *input_data, DATA1D *output_data, int input_height, int input_width, int num_channels);
void min_pooling(Layer *pooling_layer, DATA1D *input_data, DATA1D *output_data, int input_height, int input_width, int num_channels);

#endif