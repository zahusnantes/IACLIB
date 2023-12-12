#include "../inc/activation.h"
#include "../inc/tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void relu(DATA3D *data) {
    for (int i = 0; i < data->shape.depth * data->shape.width * data->shape.height; ++i) {
        data->raw_data[i] = fmax(0, data->raw_data[i]);
    }
}

void sigmoid(DATA3D *data) {
    for (int i = 0; i < data->shape.depth * data->shape.width * data->shape.height; ++i) {
        data->raw_data[i] = 1 / (1 + exp(-data->raw_data[i]));
    }
}

void softmax(DATA3D *data) {
    double max_val = data->raw_data[0];
    for (int i = 1; i < data->shape.depth * data->shape.width * data->shape.height; ++i) {
        if (data->raw_data[i] > max_val) {
            max_val = data->raw_data[i];
        }
    }

    double sum = 0.0;
    for (int i = 0; i < data->shape.depth * data->shape.width * data->shape.height; ++i) {
        data->raw_data[i] = exp(data->raw_data[i] - max_val);
        sum += data->raw_data[i];
    }

    for (int i = 0; i < data->shape.depth * data->shape.width * data->shape.height; ++i) {
        data->raw_data[i] /= sum;
    }
}

void apply_activation(DATA3D *data, Activation activation) {
    switch (activation) {
        case RELU:
            relu(data);
            break;
        case SIGMOID:
            sigmoid(data);
            break;
        case SOFTMAX:
            softmax(data);
            break;
        default:
            fprintf(stderr, "Unknown activation type. No activation applied.\n");
    }
}