#include "cnn_ops.h"
#include "tools.h"

#include <stdlib.h>
#include <stdio.h>

bool conv2D(DATA3D *input, DATA3D *output, CNNKernels *kernel)
{
    for (int dO = 0; dO < output->shape.depth + 1; dO++)
    { // looping to construct the d^th 2D convolution

        for (int h = 0; h < input->shape.height - kernel->shape.height + 1; h += kernel->stride)
        {
            for (int w = 0; w < input->shape.width - kernel->shape.width + 1; w += kernel->stride)
            {
                int position = h * input->shape.width + w;
                output->raw_data[dO*output->shape.width*output->shape.height + (h / kernel->stride) * (input->shape.width/kernel->stride)] = 0;//[h / kernel->stride][w / kernel->stride] = 0; this line will be rewritten
                for (int dI = 0; dI < input->shape.depth; dI++)
                {
                    for (int kh = 0; kh < kernel->shape.height; kh++)
                    {
                        for (int kw = 0; kw < kernel->shape.width; kw++)
                        {
                            int vd = d + kd - PADDING_DEPTH;
                            int vh = h + kh - PADDING_HEIGHT;
                            int vw = w + kw - PADDING_WIDTH;

                            if (vd >= 0 && vd < VOLUME_DEPTH &&
                                vh >= 0 && vh < VOLUME_HEIGHT &&
                                vw >= 0 && vw < VOLUME_WIDTH)
                            {
                                result[d / STRIDE_DEPTH][h / STRIDE_HEIGHT][w / STRIDE_WIDTH] +=
                                    volume[vd][vh][vw] * kernel[kd][kh][kw];
                            }
                        }
                    }
                }
            }
        }
    }
}

return false;
}

bool conv(Layer *layer)
{
    return false;
}
bool pool(Layer *layer)
{
    return false;
}
bool fc(Layer *layer)
{
    return false;
}