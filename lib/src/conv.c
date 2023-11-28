#include "../inc/conv.h"
#include "../inc/tools.h"

#include <stdlib.h>
#include <stdio.h>

bool conv(Layer *conv_layer, DATA2D *input_data, DATA3D *output_data) {
    if (conv_layer->type != CONVOLUTION) {
        fprintf(stderr, "Error: Layer is not a convolution layer.\n");
        return;
    }

    int kernel_size = conv_layer->params.kernels.shape.width;
    int stride = conv_layer->params.kernels.stride;
    int padding = conv_layer->params.kernels.padding;
    int num_output_channels = conv_layer->params.kernels.shape.depth;
    // int output_width = (INPUT_WIDTH - KERNEL_WIDTH + 2 * PADDING) / STRIDE + 1;
    // int output_height = (INPUT_HEIGHT - KERNEL_HEIGHT + 2 * PADDING) / STRIDE + 1;

    // for (int f = 0; f < NUM_FILTERS; ++f) {
    //     for (int i = 0; i < output_height; ++i) {
    //         for (int j = 0; j < output_width; ++j) {
    //             output[f * output_height * output_width + i * output_width + j] = 0.0;

    //             for (int k = 0; k < KERNEL_HEIGHT; ++k) {
    //                 for (int l = 0; l < KERNEL_WIDTH; ++l) {
    //                     int input_row = i * STRIDE + k - PADDING;
    //                     int input_col = j * STRIDE + l - PADDING;

    //                     if (input_row >= 0 && input_row < INPUT_HEIGHT &&
    //                         input_col >= 0 && input_col < INPUT_WIDTH) {
    //                         output[f * output_height * output_width + i * output_width + j] +=
    //                             input[input_row * INPUT_WIDTH + input_col] * kernel[f * KERNEL_HEIGHT * KERNEL_WIDTH + k * KERNEL_WIDTH + l];
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
}