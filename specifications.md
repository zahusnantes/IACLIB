# Specifications

## Data

The project involves working with various data structures to represent input data for the Convolutional Neural Network (CNN). Here are the key configurations related to the data structures defined in the project:

### Data Types

The data structures in the project use the following types:

- **WEIGHT_TYPE:** Type for representing weights in the CNN.
- **DATA_TYPE:** Type for representing raw data.
- **WEIGHT_PARSE_SIGNATURE:** Signature for parsing weights.

### Data Shapes

The data structures define shapes to represent different dimensions of the input data:

- **Shape1D:** Represents a 1-dimensional shape.
- **Shape2D:** Represents a 2-dimensional shape (width, height).
- **Shape3D:** Represents a 3-dimensional shape (width, height, depth).
- **Shape4D:** Represents a 4-dimensional shape (width, height, depth, num_images) - designed for image batches.

### Data Structures

The project utilizes various data structures to handle different types of data:

- **DATA1D:** Represents 1-dimensional data with a specified shape.
- **DATA2D:** Represents 2-dimensional data with a specified shape.
- **DATA3D:** Represents 3-dimensional data with a specified shape.
- **DATA4D:** Represents 4-dimensional data (batch of images) with a specified shape.

## Layers

### pooling()

#### Description

- The `pooling()` function performs pooling operations on the input data.

### max_pooling()

#### Description

- The `max_pooling()` function performs max pooling operations on the input data.

#### Interface

##### Invariants

- Describe any invariants applicable to the function.

##### Inputs

- Specify the input parameters required by the function.

##### Outputs

- Specify the output parameters produced by the function.

##### Detailed Design

- Provide additional details on the design and implementation of the `max_pooling()` function.
