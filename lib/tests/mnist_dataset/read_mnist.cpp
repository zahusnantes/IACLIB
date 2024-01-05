#include <iostream>
#include <fstream>
#include <zlib.h>

#include "../inc/tools.h"
#include "../inc/data.h"
#include "read_mnist.hpp"

DATA4D read_mnist_images(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open image file: " << filename << std::endl;
        return {Shape4D{0, 0, 0, 0}, nullptr};
    }

    // Decompress the gzip file using zlib
    gzFile gzfile = gzopen(filename.c_str(), "rb");
    if (!gzfile) {
        std::cerr << "Failed to open gzip file: " << filename << std::endl;
        return {Shape4D{0, 0, 0, 0}, nullptr};
    }

    int magic_number, num_images, num_rows, num_cols;
    gzread(gzfile, reinterpret_cast<char *>(&magic_number), sizeof(magic_number));
    gzread(gzfile, reinterpret_cast<char *>(&num_images), sizeof(num_images));
    gzread(gzfile, reinterpret_cast<char *>(&num_rows), sizeof(num_rows));
    gzread(gzfile, reinterpret_cast<char *>(&num_cols), sizeof(num_cols));

    // Perform endianness conversion
    magic_number = __builtin_bswap32(magic_number);
    num_images = __builtin_bswap32(num_images);
    num_rows = __builtin_bswap32(num_rows);
    num_cols = __builtin_bswap32(num_cols);

    // Create a Shape4D structure
    Shape4D shape{num_cols, num_rows, 1, num_images};

    // Allocate memory for raw_data
    DATA_TYPE *raw_data = new DATA_TYPE[num_images * num_rows * num_cols];

    // Read and normalize pixel data
    for (int i = 0; i < num_images; ++i) {
        for (int j = 0; j < num_rows; ++j) {
            for (int k = 0; k < num_cols; ++k) {
                unsigned char pixel;
                gzread(gzfile, reinterpret_cast<char *>(&pixel), sizeof(pixel));
                raw_data[i * num_rows * num_cols + j * num_cols + k] = static_cast<DATA_TYPE>(pixel) / 255.0;
            }
        }
    }

    // Close the gzip file
    gzclose(gzfile);

    // Create a DATA4D structure and return it
    return {shape, raw_data};
}

void free_data_4D(DATA4D &data) {
    delete[] data.raw_data;
}

void free_data_1D(DATA1D &data) {
    delete[] data.raw_data;
}


DATA1D read_mnist_labels(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open MNIST label file: " << filename << std::endl;
        return {Shape1D{0}, nullptr};
    }

    int magic_number, num_labels;
    file.read(reinterpret_cast<char *>(&magic_number), sizeof(magic_number));
    file.read(reinterpret_cast<char *>(&num_labels), sizeof(num_labels));

    magic_number = __builtin_bswap32(magic_number);
    num_labels = __builtin_bswap32(num_labels);

    // Allocate memory for raw_data
    DATA_TYPE *labels = new DATA_TYPE[num_labels];

    for (int i = 0; i < num_labels; ++i) {
        unsigned char label;
        file.read(reinterpret_cast<char *>(&label), sizeof(label));
        labels[i] = static_cast<DATA_TYPE>(label);
    }

    return {Shape1D{num_labels}, labels};
}


    // TO PRINT IMAGES AND LABELS
    // if (mnist_data.raw_data != nullptr && mnist_labels_data.raw_data != nullptr) {
    //     int num_rows = mnist_data.shape.height;
    //     int num_cols = mnist_data.shape.width;

    //     for (int i = 0; i < num_rows; ++i) {
    //         for (int j = 0; j < num_cols; ++j) {
    //             std::cout << std::setw(5) << mnist_data.raw_data[0 * num_rows * num_cols + i * num_cols + j] << " ";
    //         }
    //         std::cout << " | Label: " << std::setw(5) << mnist_labels_data.raw_data[i] << std::endl;
    //     }
    //     free_data_4D(mnist_data);
    //     free_data_1D(mnist_labels_data);
    // } else {
    //     std::cerr << "Failed to load image or label data." << std::endl;
    // }