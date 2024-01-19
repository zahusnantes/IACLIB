# Perfomances testing for Convolutional Neural Networks (CNN)

**Description:**

Welcome to the Convolutional Neural Network (CNN) Inference Library!

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [User Guide](#userguide)
    1. [Network Definition](#network-definition)
        1. [Convolution Layer](#convolution-layer-convx)
        2. [Pooling Layer](#pooling-layer-poolx)
        3. [Fully Connected Layer](#fully-connected-layer-fcx)
        4. [Reading the model](#reading-the-model)
    2. [Model Parameters](#model-parameters)
        1. [Reading the Parameters](#reading-the-parameters)
    3. [Inference](#inference)
        1. [Usage Example](#usage-example)
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
4. [Specifications](specifications.md)
  1. [Data](#data)
      1. [Data Types](specifications.md#data-types)
      2. [Data Shapes](specifications.md#data-shapes)
      3. [Data Structures](specifications.md#data-structures)
	2. [Layers](specifications.md#layers-1)
		1. [Convolution](specifications.md#convolution)
		2. [Pooling](specifications.md#pooling)
		3. [Fully Connected](specifications.md#fully-connected)
5. [Testing](#testing)

## Prerequisites

- CUDA Toolkit (Version 10.2): The project relies on CUDA for GPU acceleration. You'll need to install the CUDA Toolkit to compile and run the CUDA code. Visit the [NVIDIA CUDA Toolkit page](https://developer.nvidia.com/cuda-toolkit) for installation instructions.
- C++ Compiler
- GPU NVIDIA Jetson Xavier: The project is designed to run on NVIDIA Jetson Xavier or other compatible GPUs.
- Infineon Aurix C397 Microcontroller: This project also supports execution on the Infineon Aurix C397 microcontroller. Ensure that you have the necessary tools and libraries installed for the Infineon Aurix platform. Refer to the Infineon Aurix documentation for detailed instructions on setting up the development environment.
- ARM CPU: In addition to GPU and microcontroller support, the project is compatible with ARM CPUs. Make sure you have a compatible ARM CPU, and install the necessary libraries and dependencies for ARM architecture. Consult your system's documentation for ARM-specific setup instructions.

## User Guide

### Network Definition
The model architecture is defined in a configuration file named `model.dat`. This file serves as a blueprint for the neural network and includes information about the layers, their types, activation functions, and parameters.

The `network` block encapsulates the entire neural network.
```protobuf
network {
  // Layers and connections go here
}
```

#### Convolution Layer (`convx`)
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

#### Pooling Layer (`poolx`)
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

#### Fully Connected Layer (`fcx`)
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

#### Reading the Model

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

### Model Parameters

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

#### Reading the Parameters
To load the parameters, like kernels, weights and biases, of a pre-trained Convolutional Neural Network (CNN) model from a .csv file, you can use the following function:
```c
// Read the model parameters from the CSV file
bool success = read_weights(cnn, model_parameters_path);
```
where:
- **cnn**: represent the CNN model already loaded.
- **model_parameters_path**: represents the path to the model parameters file.

### Inference

To perform inference with the trained Convolutional Neural Network (CNN), you can use the `inference` function. This function takes the CNN model and input data as parameters.

```c
inference(cnn, &input);
```
where:

- **cnn**: The CNN model loaded from the .dat file using the read_model function.

- **input**: A DATA3D structure representing the input image for inference.

#### Usage Example

Here's an example of how to perform inference:
```c
// Load the CNN model from the .dat file
CNN *cnn = read_model("your_model.dat", /* other parameters */);

// Read the model parameters from the CSV file
bool success = read_weights(cnn, model_parameters_path);

// Prepare input data (replace this with your actual data)
DATA3D input;
// Initialize input data with proper values
// ...

// Perform inference
inference(cnn, &input);
```

## Requirements

For detailed functional and non-functional requirements, please refer to the [Requirements](requirements.md) document.

## Specifications

For detailed specifications, please refer to the [Specifications](specifications.md) document.