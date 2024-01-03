#include <gtest/gtest.h>

#include "test_conv.cpp"
#include "test_pooling.cpp"
#include "test_fc.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}