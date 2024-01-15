# Requirements

## Functional Requirements

### Configurations

The project involves working with various data structures to represent input data for the Convolutional Neural Network (CNN). Here are the key configurations related to the data structures defined in the project:

#### Data Types

The data structures in the project use the following types:

- **WEIGHT_TYPE:** Type for representing weights in the CNN.
- **DATA_TYPE:** Type for representing raw data.
- **WEIGHT_PARSE_SIGNATURE:** Signature for parsing weights.

#### Data Shapes

The data structures define shapes to represent different dimensions of the input data:

- **Shape1D:** Represents a 1-dimensional shape.
- **Shape2D:** Represents a 2-dimensional shape (width, height).
- **Shape3D:** Represents a 3-dimensional shape (width, height, depth).
- **Shape4D:** Represents a 4-dimensional shape (width, height, depth, num_images) - designed for image batches.

#### Data Structures

The project utilizes various data structures to handle different types of data:

- **DATA1D:** Represents 1-dimensional data with a specified shape.
- **DATA2D:** Represents 2-dimensional data with a specified shape.
- **DATA3D:** Represents 3-dimensional data with a specified shape.
- **DATA4D:** Represents 4-dimensional data (batch of images) with a specified shape.

#### Model Configuration

The model architecture is defined in a configuration file named `model.dat`. This file serves as a blueprint for the neural network and includes information about the layers, their types, activation functions, and parameters.

##### Network Definition

The `network` block encapsulates the entire neural network.
<pre>
```
network {
  // Layers and connections go here
}

layer {
  name: "conv1"
  type: "Convolution"
  activation: RELU
  bottom: "input_layer_name"
  top: "output_layer_name"
  convolution_param {
    num_output: 64  # Number of output channels
    kernel_size: 3  # Size of the convolutional kernel
    stride: 1       # Stride for the convolution operation
    pad: 1          # Padding for the input data
  }
}

layer {
  name: "pool1"
  type: "Pooling"
  activation: RELU
  bottom: "input_layer_name"
  top: "output_layer_name"
  pooling_param {
    pool: AVG  # Pooling type (MAX, AVG, MIN)
    kernel_size: 2  # Size of the pooling kernel
    stride: 2       # Stride for the pooling operation
  }
}

layer {
  name: "conv1"
  type: "Convolution"
  activation: RELU
  bottom: "input_layer_name"
  top: "output_layer_name"
  convolution_param {
    num_output: 64  # Number of output channels
    kernel_size: 3  # Size of the convolutional kernel
    stride: 1       # Stride for the convolution operation
    pad: 1          # Padding for the input data
  }
}
```
</pre>

### Inference

#### Layers

##### Convolution

The convolution layer in the project performs spatial filtering on input data using convolutional kernels. To ensure proper usage and understanding, here are the key details and requirements related to the convolution layer:

- **Input Format:**
  - The input data should be a 3D tensor with dimensions (depth, height, width) representing the input channels, height, and width, respectively.

- **Output Format:**
  - The output of the convolution layer  should be a 3D tensor and is automatically calculated during the layer definition using the `compute_layer_conv_params` function. The dimensions of the output tensor are determined by the configuration parameters of the convolutional kernels, including the number of output channels, height, and width.

- **Convolution Functionality:**
  - The convolution layer utilizes a set of convolutional kernels to perform spatial filtering.
  - The convolution operation includes parameters such as kernel size, padding, and stride, which can be configured in the convolution layer.

- **Implementation Considerations:**
  - The convolution layer implementation is provided in the `conv.c` file.
  - Ensure that the input layer specified is indeed a convolutional layer before invoking the convolution function.

- **Usage Example:**
  ```c
  // Example usage of the convolution layer
  Layer convolution_layer;
  // Initialize convolution_layer with appropriate parameters
  // ...

  DATA3D input_data; // Initialize input_data with proper values
  DATA3D output_data; // The output_data will be populated after applying the convolution

  // Apply convolution
  bool success = conv(&convolution_layer, &input_data, &output_data);

  if (success) {
    // The output_data tensor is automatically updated during layer initialization
    // No separate calculation needed for the output format
  } else {
      fprintf(stderr, "Convolution layer failed to execute.\n");
  }

##### Pooling

The pooling layer in the project is responsible for downsampling the input data using pooling operations such as max, average, or min pooling. Here are the key details and requirements related to the pooling layer:

- **Supported Pooling Types:**
  - The pooling layer supports three types of pooling operations: MAX, AVG, and MIN.
  - Specify the desired pooling type in the configuration parameters.

- **Input Format:**
  - The input data should be a 3D tensor with dimensions (depth, height, width) representing the input channels, height, and width, respectively.

- **Output Format:**
  - The output of the pooling layer should be a 3D tensor and is automatically calculated during the layer definition using the `compute_layer_pool_params` function. The dimensions of the output tensor are determined by the configuration parameters of the pooling operation, including the pooling type, pool size, padding, and stride.

- **Pooling Functionality:**
  - The pooling layer performs downsampling based on the specified pooling type.
  - Pooling parameters include pool size, padding, and stride, which can be configured in the pooling layer.

- **Implementation Considerations:**
  - The pooling layer implementation is provided in the `pooling.c` file.
  - Ensure that the input layer specified is a valid pooling layer before invoking the pooling function.

- **Usage Example:**
  ```c
  // Example usage of the pooling layer
  Layer pooling_layer;
  // Initialize pooling_layer with appropriate parameters
  // ...

  DATA3D input_data; // Initialize input_data with proper values
  DATA3D output_data; // The output_data will be populated after applying the pooling operation

  // Apply pooling
  bool success = pooling(&pooling_layer, &input_data, &output_data);

  if (success) {
    // The output_data tensor is automatically updated during layer initialization
    // No separate calculation needed for the output format
  } else {
      fprintf(stderr, "Pooling layer failed to execute.\n");
  }

##### Fully Connected

The fully connected (FC) layer in the project performs a linear transformation on the input data, connecting all neurons of the layer to every input. Here are the key details and requirements related to the fully connected layer:

- **Input Format:**
  - The input data should be a 3D tensor with dimensions (depth, height, width) representing the input channels, height, and width, respectively.

- **Output Format:**
  - The output of the fully connected layer should be a 1D tensor and is automatically calculated during the layer definition using the `compute_layer_fc_params` function. The dimensions of the output tensor are determined by the number of neurons specified in the fully connected layer configuration.

- **Fully Connected Layer Functionality:**
  - The fully connected layer performs a linear transformation on the input data.
  - The layer is specified by a set of weights and biases.

- **Implementation Considerations:**
  - The fully connected layer implementation is provided in the `fc.c` file.
  - Ensure that the input layer specified is indeed a fully connected layer before invoking the `fc` function.

- **Usage Example:**
  ```c
  // Example usage of the fully connected layer
  Layer fc_layer;
  // Initialize fc_layer with appropriate parameters
  // ...

  DATA3D input_data; // Initialize input_data with proper values
  DATA3D output_data; // The output_data will be populated after applying the fully connected layer

  // Apply the fully connected layer
  bool success = fc(&fc_layer, &input_data, &output_data);

  if (success) {
    // The output_data tensor is automatically updated during layer initialization
    // No separate calculation needed for the output format
  } else {
      fprintf(stderr, "Fully connected layer failed to execute.\n");
  }


#### Operation Types

##### CPU Operations

- Describe any specific requirements for CPU-based operations.

##### CUDA Operations

- Specify requirements for CUDA-based operations.

## Non-Functional Requirements

### Runtime Environment

#### Operating System

##### Linux

- Specify Linux-specific requirements.

##### Bare Metal

- If applicable, include requirements for running on bare metal.

#### Platform

##### x86 CPU

- Include any requirements related to x86 architecture.

##### NVIDIA CUDA GPU

- Specify requirements for GPUs.

##### ARM CPU

- Specify requirements for ARM architecture.

#### Source