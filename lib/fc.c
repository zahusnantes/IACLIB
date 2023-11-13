#include "fc.h"
#include "tools.h"

#include <stdlib.h>
#include <stdio.h>

FCLayer(int input_units, int output_units, double alpha) : input_units(input_units), output_units(output_units), alpha(alpha) {
    weight.resize(input_units, image1D(output_units, 0.0));
    bias.resize(output_units, 0.0);

    // Random number generator with a normal distribution
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    // Generate random numbers and store them in the output vector
    for (int i = 0; i < input_units; ++i) {
        for (int j = 0; j < output_units; ++j) {
            weight[i][j] = distribution(generator);
        }
    }
}

image1D forward_prop(const image1D& flattened_input) override {

    output.resize(output_units, 0.0);
    for (int j = 0; j < output_units; ++j) {
        for (int l = 0; l < input_units; ++l) {
            output[j] += flattened_input[l] * weight[l][j];
        }
        output[j] += bias[j];
    }

    // Apply softmax activation
    double max_val = std::numeric_limits<double>::lowest();
    for (double val : output) {
        max_val = std::max(max_val, val);
    }
    double exp_sum = 0.0;
    std::vector<double> softmax_output(output_units, 0.0);
    for (int i = 0; i < output_units; ++i) {
        softmax_output[i] = exp(output[i] - max_val);
        exp_sum += softmax_output[i];
    }
    for (int i = 0; i < output_units; ++i) {
        softmax_output[i] /= exp_sum;
    }

    return softmax_output;
}