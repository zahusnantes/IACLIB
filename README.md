# Perfomances testing for Convolutional Neural Networks (CNN)

**Description:**

Welcome to the CUDA Convolutional Neural Network (CNN) Inference Library!

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Requirements](#requirements)
	1. [Functional](#functional)
   		1. [Configurations](#configurations)
   			1. [Models](#models)
      				1. [JSON Formatted Model](#json-formatted-model)
   		2. [Inference](#inference)
      			1. [Layers](#layers)
         			1. [Convolution](#convolution)
         			2. [Max Pooling](#max-pooling)
         			3. [Fully Connected](#fully-connected)
            		2. [Operation Types](#operation-types)
               			1. [CPU Operations](#cpu-operations)
               			2. [CUDA Operations](#cuda-operations)
	2. [Non-Functional](#non-functional)
		1. [Runtime Environment](#runtime-environment)
            		1. [Operating System](#operating-system)
               			1. [Linux](#linux)
                  		2. [Bare Metal](#bare-metal)
            		2. [Platform](#platform)
               			1. [x86 CPU](#x86-cpu)
               			2. [NVIDIA CUDA GPU](#nvidia-cuda-gpu)
               			3. [ARM CPU](#arm-cpu)
            		3. [Linking](#linking)
               			1. [Dynamic Binary](#dynamic-binary)
               			2. [Static Binary](#static-binary)
            			3. [Source](#source)
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

