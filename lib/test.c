#include <gtest/gtest.h>

// Include your header file with the conv function and data structures
#include "conv.h"

// Define a test fixture
class ConvTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize any necessary resources before each test
    }

    void TearDown() override {
        // Clean up any resources after each test
    }
};

// Test the conv function
TEST_F(ConvTest, ConvolutionTest) {
    // Define input data
    DATA1D input;
    initialize_DATA1D(&input, 5);  // Adjust the size as needed

    // Define output data
    DATA1D output;
    initialize_DATA1D(&output, 3);  // Adjust the size as needed

    // Define kernel data
    CNNKernels kernel;
    initialize_CNNKernels(&kernel, 3, 1, 1, 1, 0);  // Adjust dimensions as needed

    // Set some example data for input, output, and kernel
    for (int i = 0; i < input.shape.length; ++i) {
        input.raw_data[i] = static_cast<DATA_TYPE>(i + 1);
    }

    // Initialize kernel values
    int kernel_values[] = {1, 2, 3};  // Adjust as needed
    for (int i = 0; i < kernel_values; ++i) {
        kernel.values[i] = static_cast<WEIGHT_TYPE>(kernel_values[i]);
    }

    // Call the convolution function
    conv(&input, &output, &kernel);

    // Define your expected output based on the input and kernel
    DATA_TYPE expected_output[] = {14, 32, 50};  // Adjust based on your convolution calculation

    // Check if the actual output matches the expected output
    for (int i = 0; i < output.shape.length; ++i) {
        EXPECT_EQ(output.raw_data[i], expected_output[i]);
    }
}

// Entry point for the test program
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
