#include "../inc/tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <../inc/images.h>

int main(int argc, char **argv)
{
    int in_h = 28;
    int in_w = 28;
    int nb_classes = 10;

    CNN *cnn = read_model("../model/model.dat", in_h, in_w, nb_classes);
    //display_cnn(cnn);
    bool success = read_weights(cnn, "../model/model_parameters.csv");

    // if (success)
    //     printf("Model parameters loaded successfully\n");
    // else
    //     fatal_error(-111, "Model parameters loading failed\n");

    Layer *conv_layer = find_layer(cnn, "conv1");

    return 0;
}
