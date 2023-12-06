#ifndef CONV_H
#define CONV_H

#include "tools.h"

bool conv(Layer *conv_layer, DATA1D *input_data, DATA3D *kernel, DATA1D *output_data, int input_height, int input_width);

#endif