#include "../inc/fc.h"
#include "../inc/tools.h"

#include <stdlib.h>
#include <stdio.h>

bool fc(Layer *fc_layer, DATA3D *input_data, DATA2D *weights, DATA1D *biases, DATA3D *output_data) {
    if (fc_layer->type != FC) {
        fprintf(stderr, "Error: Layer is not a fully connected (FC) layer.\n");
        return false;
    }

    int num_neurons = fc_layer->params.fc.shape.length;
    int input_size = layer_data_size(fc_layer->bottom);
    
    if (weights->shape.height != num_neurons || weights->shape.width != input_size) {
        fprintf(stderr, "Error: FC layer dimensions mismatch.\n");
        return false;
    }

    // Perform FC layer computation
    for (int neuron_idx = 0; neuron_idx < num_neurons; ++neuron_idx) {
        WEIGHT_TYPE sum = 0.0;

        for (int input_idx = 0; input_idx < input_size; ++input_idx) {
            sum += input_data->raw_data[input_idx] * weights->raw_data[neuron_idx * input_size + input_idx];
        }

        // Add bias
        sum += biases->raw_data[neuron_idx];

        // Assign the result to the output
        output_data->raw_data[neuron_idx] = sum;
    }

    return true;
}
