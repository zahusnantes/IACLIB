#include "../inc/conv.h"
#include "../inc/tools.h"

#include <stdlib.h>
#include <stdio.h>

bool conv(Layer *conv_layer, DATA3D *input_data, DATA3D *output_data) {
    if (conv_layer->type != CONVOLUTION) {
        fprintf(stderr, "Error: Layer is not a convolution layer.\n");
        return false;
    }
    CNNKernels *conv_params = &(conv_layer->params.kernels);
    WEIGHT_TYPE *conv_weights = conv_params->values;
    WEIGHT_TYPE *conv_biases = conv_params->bias;

    int input_channels = input_data->shape.depth;
    int input_width = input_data->shape.width;
    int input_height = input_data->shape.height;
    int input_size = input_height * input_width * input_channels;
    int kernel_size = conv_layer->params.kernels.shape.width;
    int padding = conv_layer->params.kernels.padding;
    int stride = conv_layer->params.kernels.stride;
    int output_height = conv_params->shape.height;
    int output_width = conv_params->shape.width;
    int num_channels = conv_params->shape.depth;
    int output_size = output_height * output_width * num_channels;

    for (int out = 0; out < output_size; ++out) {
        for (int c_output = 0; c_output < num_channels; ++c_output) {
            for (int h = 0; h < output_height; ++h) {
                for (int w = 0; w < output_width; ++w) {

                    WEIGHT_TYPE sum = conv_biases[c_output]; 

                    for (int i = 0; i < kernel_size; ++i) {
                        for (int j = 0; j < kernel_size; ++j) {
                            for (int c_input = 0; c_input < input_channels; ++c_input) {
                                int input_idx = (h * stride + i) * input_width * input_channels + (w * stride + j) * input_channels + c_input;
                                int kernel_idx = c_output * (kernel_size * kernel_size * input_channels) + i * (kernel_size * input_channels) + j * input_channels + c_input;
                                double input_pixel = input_data->raw_data[input_idx];
                                double kernel_value = conv_weights[kernel_idx];
                                sum += input_pixel * kernel_value;
                            }
                        }
                    }

                    int output_idx = c_output * output_width * output_height + h * output_width + w;
                    output_data->raw_data[output_idx] = sum;
                }
            }
        }
    }

    return true;
}
