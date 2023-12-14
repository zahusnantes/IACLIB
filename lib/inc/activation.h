#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "tools.h"
#include "data.h"

#ifdef __cplusplus
extern "C" {
#endif

void relu(DATA3D *data);
void sigmoid(DATA3D *data);
void softmax(DATA3D *data);
void apply_activation(DATA3D *data, Activation activation);

#ifdef __cplusplus
}
#endif

#endif