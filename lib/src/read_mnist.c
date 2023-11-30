#include "../inc/tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <../inc/images.h>
#include <../inc/read_mnist.h>

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