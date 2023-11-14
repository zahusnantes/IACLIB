cmake_minimum_required(VERSION 3.14)

project(CNN_INFERENCE)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(googletest/include)

add_executable(test_convlayer test_convlayer.cpp ConvolutionLayer.h)
add_executable(test_maxpoollayer test_maxpoollayer.cpp MaxPoolingLayer.h)
add_executable(test_FClayer test_FClayer.cpp FCLayer.h)

target_link_libraries(test_convlayer gtest gtest_main pthread)
target_link_libraries(test_maxpoollayer gtest gtest_main pthread)
target_link_libraries(test_FClayer gtest gtest_main pthread)