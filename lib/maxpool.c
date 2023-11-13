#include "maxpool.h"
#include "tools.h"

#include <stdlib.h>
#include <stdio.h>

MaxPoolingLayer(int decimation) : m_decimation(decimation) {}

image3D forward_prop(const image3D& image) override {
    int image_h = image.size();
    int image_w = image[0].size();
    int channels = image[0][0].size();
    int output_h = image_h / m_decimation;
    int output_w = image_w / m_decimation;
    image3D max_pooling_output(output_h, image2D(output_w, image1D(channels, 0.0)));

    for (int h = 0; h < output_h; ++h) {
        for (int w = 0; w < output_w; ++w) {
            for (int c = 0; c < channels; ++c) {
                double max_val = image[h * m_decimation][w * m_decimation][c];
                for (int i = 0; i < m_decimation; ++i) {
                    for (int j = 0; j < m_decimation; ++j) {
                        max_val = std::max(max_val, image[h * m_decimation + i][w * m_decimation + j][c]);
                    }
                }
                max_pooling_output[h][w][c] = max_val;
            }
        }
    }

    return max_pooling_output;
}