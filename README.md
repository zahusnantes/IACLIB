# Perfomances testing for Convolutional Neural Networks (CNN)

**Description:**

Welcome to the Convolutional Neural Network (CNN) Inference Library!

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [User Guide](#userguide)
    1. [Data](#data)
        1. [Data Types](#data-types)
        2. [Data Shapes](#data-shapes)
        3. [Data Structures](#data-structures)
        4. [Network Definition](#network-definition)
            1. [Convolution Layer](#convolution-layer-convx)
            2. [Pooling Layer](#pooling-layer-poolx)
            3. [Fully Connected Layer](#fully-connected-layer-fcx)
            4. [Reading the model](#reading-the-model)
        5. [Model Parameters](#model-parameters)
            1. [Reading the Parameters](#reading-the-parameters)
3. [Requirements](requirements.md)
    1. [Functional](requirements.md#functional)
        1. [Configurations](requirements.md#configurations)
        2. [Inference](requirements.md#inference)
            1. [Layers](requirements.md#layers)
                1. [Convolution](requirements.md#convolution)
                2. [Pooling](requirements.md#pooling)
                3. [Fully Connected](requirements.md#fully-connected)
            2. [Operation Types](requirements.md#operation-types)
                1. [CPU Operations](requirements.md#cpu-operations)
                2. [CUDA Operations](requirements.md#cuda-operations)
    2. [Non-Functional](requirements.md#non-functional)
        1. [Runtime Environment](requirements.md#runtime-environment)
            1. [Operating System](requirements.md#operating-system)
                1. [Linux](requirements.md#linux)
                    1. [Bare Metal](requirements.md#bare-metal)
            2. [Platform](requirements.md#platform)
                1. [x86 CPU](requirements.md#x86-cpu)
                2. [NVIDIA CUDA GPU](requirements.md#nvidia-cuda-gpu)
                3. [ARM CPU](requirements.md#arm-cpu)
            3. [Source](requirements.md#source)
4. [Specifications](#specifications)
	1. [Layers](#layers-1)
		1. [pooling()](#pooling)
			1. [Description](#description)
		2. [max_pooling()](#max_pooling)
			1. [Description](#description-1)
			2. [Interface](#interface)
				1. [Invariants](#invariants)
				2. [Inputs](#inputs)
				3. [Outputs](#outputs)
				4. [Detailed Design](#detailed-design)
5. [Testing](#testing)

## Prerequisites

- CUDA Toolkit (Version 10.2): The project relies on CUDA for GPU acceleration. You'll need to install the CUDA Toolkit to compile and run the CUDA code. Visit the [NVIDIA CUDA Toolkit page](https://developer.nvidia.com/cuda-toolkit) for installation instructions.
- C++ Compiler
- GPU NVIDIA Jetson Xavier: The project is designed to run on NVIDIA Jetson Xavier or other compatible GPUs.
- Infineon Aurix C397 Microcontroller: This project also supports execution on the Infineon Aurix C397 microcontroller. Ensure that you have the necessary tools and libraries installed for the Infineon Aurix platform. Refer to the Infineon Aurix documentation for detailed instructions on setting up the development environment.
- ARM CPU: In addition to GPU and microcontroller support, the project is compatible with ARM CPUs. Make sure you have a compatible ARM CPU, and install the necessary libraries and dependencies for ARM architecture. Consult your system's documentation for ARM-specific setup instructions.

## User Guide

### Data

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

#### Network Definition
The model architecture is defined in a configuration file named `model.dat`. This file serves as a blueprint for the neural network and includes information about the layers, their types, activation functions, and parameters.

The `network` block encapsulates the entire neural network.
```protobuf
network {
  // Layers and connections go here
}
```

##### Convolution Layer (`convx`)
Here is an example of a convolution layer in the neural network:

- **Type:** Convolution
- **Activation Function:** RELU (Rectified Linear Unit)
- **Input Layer (`bottom`):** "data"
- **Output Layer (`top`):** "convx"
- **Convolution Parameters:**
  - Number of Output Channels (`num_output`): 2
  - Kernel Size (`kernel_size`): 2
  - Stride (`stride`): 1
  - Padding (`pad`): 0

```protobuf
layer {
  name: "convx"
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

##### Pooling Layer (`poolx`)
Here is an example of a pooling layer in the neural network:

- **Type:** Pooling
- **Activation Function:** RELU
- **Input Layer (`bottom`):** "convx"
- **Output Layer (`top`):** "fcx"
- **Pooling Parameters:**
  - Pooling Type (`pool`): AVG (Average Pooling)
  - Kernel Size (`kernel_size`): 2
  - Stride (`stride`): 1

<pre>
layer {
  name: "poolx"
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
</pre>

##### Fully Connected Layer (`fcx`)
Here is an example of a fully connected layer in the neural network:

- **Type:** InnerProduct
- **Activation Function:** SOFTMAX
- **Input Layer (`bottom`):** "poolx"
- **Output Layer (`top`):** "output"
- **Inner Product Parameters:**
  - Number of Output Neurons (`num_output`): 2

<pre>
layer {
  name: "fcx"
  type: "InnerProduct"
  activation: SOFTMAX
  bottom: "poolx"
  top: "output"
  inner_product_param {
    num_output: 2
  }
}
</pre>

##### Reading the Model

To load a pre-trained Convolutional Neural Network (CNN) model from a .dat file, you can use the following function:

  ```c
  CNN *cnn = read_model(model_path, input.shape.height, input.shape.width, input.shape.depth, number_of_classes);
  ```
where:

- **model_path**: represents the path to the model file.

- **input.shape.height**: represent the height of the input.

- **input.shape.width**: represent the width of the input.

- **input.shape.depth**: represent the depth of the input.

- **number_of_classes**:represent the number of classes in the model.

#### Model Parameters

The CNN model parameters, including weights and biases, are stored in a CSV file. The file structure follows a specific format, where each line represents a layer parameter.
The CSV file should have the following structure:

```csv
convx.weight, //parameters
convx.bias, //parameters
fcx.weight, //parameters
fcx.bias, //parameters
```
- Each line corresponds to a layer parameter.
- The first part before the comma represents the layer name and the type of parameter (weight or bias).
- The subsequent values, separated by commas, are the actual parameter values.

##### Reading the Parameters
To load the parameters, like kernels, weights and biases, of a pre-trained Convolutional Neural Network (CNN) model from a .csv file, you can use the following function:
```c
// Read the model parameters from the CSV file
bool success = read_weights(cnn, model_parameters_path);
```
where:
- **cnn**: represent the CNN model already loaded.
- **model_parameters_path**: represents the path to the model parameters file.

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


## Requirements

For detailed functional and non-functional requirements, please refer to the [Requirements](requirements.md) document.