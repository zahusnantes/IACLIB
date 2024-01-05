#include "../inc/fc.h"
#include "../inc/tools.h"

#include <stdlib.h>
#include <stdio.h>

bool fc(Layer *fc_layer, DATA3D *input_data, DATA3D *output_data) {
    if (fc_layer->type != FC) {
        fprintf(stderr, "Error: Layer is not a fully connected (FC) layer.\n");
        return false;
    }

    int num_neurons = fc_layer->params.fc.shape.length;
    int input_size = layer_data_size(fc_layer->bottom);

    CNNFc *fc_params = &(fc_layer->params.fc);
    WEIGHT_TYPE *weights = fc_params->values;
    WEIGHT_TYPE *biases = fc_params->bias;

    for (int neuron_idx = 0; neuron_idx < num_neurons; ++neuron_idx) {
        WEIGHT_TYPE sum = 0.0;

        for (int input_idx = 0; input_idx < input_size; ++input_idx) {
            sum += input_data->raw_data[input_idx] * weights[neuron_idx * input_size + input_idx];
        }

        sum += biases[neuron_idx];

        output_data->raw_data[neuron_idx] = sum;
    }

    return true;
}
