#include "../inc/tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <../inc/images.h>

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

Image read_mnist_images(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open image file");
        exit(EXIT_FAILURE);
    }

    ImageHeader header;
    fread(&header, sizeof(header), 1, file);

    header.magic_number = __builtin_bswap32(header.magic_number);
    header.num_images = __builtin_bswap32(header.num_images);
    header.num_rows = __builtin_bswap32(header.num_rows);
    header.num_cols = __builtin_bswap32(header.num_cols);

    Image images;
    images.pixels = malloc(header.num_images * sizeof(unsigned char *));
    for (int i = 0; i < header.num_images; ++i) {
        images.pixels[i] = malloc(header.num_rows * header.num_cols);
        fread(images.pixels[i], 1, header.num_rows * header.num_cols, file);
    }

    fclose(file);

    return images;
}

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

    if (success)
        printf("Model parameters loaded successfully\n");
    else
        fatal_error(-111, "Model parameters loading failed\n");

    Layer *conv_layer = find_layer(cnn, "conv1");

    // Now you can use 'conv_layer' and 'test_images' for further processing

    // Free the allocated memory for test images
    for (int i = 0; i < test_images.num_images; ++i) {
        free(test_images.pixels[i]);
    }
    free(test_images.pixels);

    // Free the allocated memory for CNN
    // Add the necessary code to free the memory in your 'read_model' and 'read_weights' functions
    // ...

    return 0;
}
