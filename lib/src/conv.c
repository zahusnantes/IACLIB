#include "../inc/conv.h"
#include "../inc/tools.h"

#include <stdlib.h>
#include <stdio.h>

// CHIARA: I need to get rid of the int input_height, int input_width and find another way of pass it to the function
bool conv(Layer *conv_layer, DATA1D *input_data, DATA1D *kernel, DATA1D *output_data, int input_height, int input_width) {
    if (conv_layer->type != CONVOLUTION) {
        fprintf(stderr, "Error: Layer is not a convolution layer.\n");
        return false;
    }
    CNNKernels *conv_params = &(conv_layer->params.kernels);

    int input_size = input_data->shape.length;
    int kernel_size = conv_params->shape.width;
    int output_size = output_data->shape.length;
    int num_channels = conv_params->shape.depth;
    int padding = conv_layer->params.kernels.padding;
    int stride = conv_layer->params.kernels.stride;
    int output_height = (input_height - kernel_size + 2 * padding) / stride + 1;
    int output_width = (input_width - kernel_size + 2 * padding) / stride + 1;
    int input_channels = 1; // CHIARA: to verify this parameter, it is set to one because it one output_channel

    // CHIARA: check here id the convolution works
    // if (output_size != num_channels * output_width * output_height) {
    //     fprintf(stderr, "Error: Output data size does not match expected size.\n");
    //     return false;
    // }

    for (int out = 0; out < output_size; ++out){
        for (int c_output = 0; c_output < num_channels; ++c_output) {
            for (int h = 0; h < output_height; ++h) {
                for (int w = 0; w < output_width; ++w) {

                    WEIGHT_TYPE sum = 0.0;

                    for (int i = 0; i < kernel_size; ++i) {
                        for (int j = 0; j < kernel_size; ++j) {
                            for (int c_input = 0; c_input < input_channels; ++c_input) {
                                int input_idx = (h * stride + i) * input_width * input_channels + (w * stride + j) * input_channels + c_input;
                                int kernel_idx = c_output * (kernel_size * kernel_size * input_channels) + i * (kernel_size * input_channels) + j * input_channels + c_input;

                                double input_pixel = input_data->raw_data[input_idx];
                                double kernel_value = kernel->raw_data[kernel_idx];
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
