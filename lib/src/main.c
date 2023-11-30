#include "../inc/tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <../inc/images.h>
#include <../inc/read_mnist.h>

#define IMAGE_MAGIC_NUMBER 2051
#define LABEL_MAGIC_NUMBER 2049

typedef struct {
    int magic_number;
    int num_images;
    int num_rows;
    int num_cols;
} ImageHeader;

typedef struct {
    unsigned char **pixels;
} Image;

int main(int argc, char **argv)
{
    const char *test_images_file = "t10k-images-idx3-ubyte.gz";
    Image test_images = read_mnist_images(test_images_file);

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

    // Free the allocated memory for test images
    for (int i = 0; i < test_images.num_images; ++i) {
        free(test_images.pixels[i]);
    }
    free(test_images.pixels);

    return 0;
}
