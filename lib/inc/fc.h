#ifndef FC_H
#define FC_H

#include "tools.h"
#include "images.h"

bool fc(Layer *fc_layer, DATA3D *input_data, DATA2D *weights, DATA1D *biases, DATA3D *output_data);

#endif