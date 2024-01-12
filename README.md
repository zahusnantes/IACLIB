# Perfomances testing for Convolutional Neural Networks (CNN)

**Description:**

Welcome to the Convolutional Neural Network (CNN) Inference Library!

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Requirements](requirements.md)
    1. [Functional](requirements.md#functional)
        1. [Configurations](requirements.md#configurations)
        2. [Inference](requirements.md#inference)
            1. [Layers](requirements.md#layers)
                1. [Convolution](requirements.md#convolution)
                2. [Max Pooling](requirements.md#max-pooling)
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
3. [Specifications](#specifications)
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
4. [Testing](#testing)

## Prerequisites

- CUDA Toolkit (Version 10.2): The project relies on CUDA for GPU acceleration. You'll need to install the CUDA Toolkit to compile and run the CUDA code. Visit the [NVIDIA CUDA Toolkit page](https://developer.nvidia.com/cuda-toolkit) for installation instructions.
- C++ Compiler
- GPU NVIDIA Jetson Xavier: The project is designed to run on NVIDIA Jetson Xavier or other compatible GPUs.
- Infineon Aurix C397 Microcontroller: This project also supports execution on the Infineon Aurix C397 microcontroller. Ensure that you have the necessary tools and libraries installed for the Infineon Aurix platform. Refer to the Infineon Aurix documentation for detailed instructions on setting up the development environment.
- ARM CPU: In addition to GPU and microcontroller support, the project is compatible with ARM CPUs. Make sure you have a compatible ARM CPU, and install the necessary libraries and dependencies for ARM architecture. Consult your system's documentation for ARM-specific setup instructions.

## Requirements

For detailed functional and non-functional requirements, please refer to the [Requirements](requirements.md) document.

