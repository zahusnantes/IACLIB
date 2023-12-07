#include "gtest/gtest.h"
#include "../inc/conv.h"
#include "../inc/tools.h"
#include "../inc/images.h"

class ConvTest : public ::testing::Test {
protected:
    // Declare members for common test data
    Layer conv_layer;
    DATA3D matrix;
    DATA3D kernel;
    DATA1D linearized_matrix;
    DATA1D linearized_kernel;
    DATA1D conv_output_data;

    virtual void SetUp() {

        // Initialize the convolution layer
        conv_layer.type = CONVOLUTION;
        conv_layer.params.kernels.shape.width = 2;
        conv_layer.params.kernels.shape.height = 2;
        conv_layer.params.kernels.shape.depth = 1;
        conv_layer.params.kernels.stride = 1;
        conv_layer.params.kernels.padding = 0;

        matrix.shape.width = 3;
        matrix.shape.height = 3;
        matrix.shape.depth = 1;
        initialize_DATA3D(&matrix, matrix.shape.height, matrix.shape.width, matrix.shape.depth);
        initialize_DATA1D(&matrix.linearized_data, matrix.shape.width * matrix.shape.height * matrix.shape.depth);
        // Initialize the 3D matrix
        for (int i = 0; i < matrix.shape.width * matrix.shape.height * matrix.shape.depth; ++i) {
            matrix.raw_data[i] = i;
        }
        // Copy data from the 3D matrix to the linearized version
        for (int i = 0; i < matrix.linearized_data.shape.length; ++i) {
            matrix.linearized_data.raw_data[i] = matrix.raw_data[i];
        }

        kernel.shape.width = 2;
        kernel.shape.height = 2;
        kernel.shape.depth = 2;
        initialize_DATA3D(&kernel, kernel.shape.height, kernel.shape.width, kernel.shape.depth);
        initialize_DATA1D(&kernel.linearized_data, kernel.shape.width * kernel.shape.height * kernel.shape.depth);
        // Initialize the 3D kernel 
        for (int i = 0; i < kernel.shape.width * kernel.shape.height * kernel.shape.depth; ++i) {
            kernel.raw_data[i] = i;
        }
        // Copy data from the 3D kernel to the linearized version
        for (int i = 0; i < kernel.linearized_data.shape.length; ++i) {
            kernel.linearized_data.raw_data[i] = kernel.raw_data[i];
        }

        // Create linearized versions of matrix and kernel
        initialize_DATA1D(&linearized_matrix, matrix.linearized_data.shape.length);
        initialize_DATA1D(&linearized_kernel, kernel.linearized_data.shape.length);

        // Copy data from the linearized matrix and kernel
        for (int i = 0; i < linearized_matrix.shape.length; ++i) {
            linearized_matrix.raw_data[i] = matrix.linearized_data.raw_data[i];
        }

        for (int i = 0; i < linearized_kernel.shape.length; ++i) {
            linearized_kernel.raw_data[i] = kernel.linearized_data.raw_data[i];
        }

        // Initialize output data
        int input_height = matrix.shape.height;
        int input_width = matrix.shape.width;
        int conv_output_height = (input_height - conv_layer.params.kernels.shape.width + 2 * conv_layer.params.kernels.padding) / conv_layer.params.kernels.stride + 1;
        int conv_output_width = (input_width - conv_layer.params.kernels.shape.width + 2 * conv_layer.params.kernels.padding) / conv_layer.params.kernels.stride + 1;
        int conv_output_depth = 1;
        int conv_output_size = conv_output_width * conv_output_height * conv_output_depth;
        initialize_DATA1D(&conv_output_data, conv_output_size);
    }

    virtual void TearDown() {
        // Clean up common test data here
        free(matrix.raw_data);
        free(kernel.raw_data);
        free(linearized_matrix.raw_data);
        free(linearized_kernel.raw_data);
        free(conv_output_data.raw_data);
    }
};

TEST_F(ConvTest, SimpleConvolution) {
    // Call the conv function
    bool result = conv(&conv_layer, &linearized_matrix, &linearized_kernel, &conv_output_data, &matrix);

    // Check the result and add assertions
    ASSERT_TRUE(result);

    // Add assertions to check the values in output_data based on your expected output
    // ...
    // Add more assertions as needed
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
