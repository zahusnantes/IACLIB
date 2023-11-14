# cmake_minimum_required(VERSION 3.0)

# option(DEBUG "Enable debugging" ON)

# include_directories("/usr/include")  # Replace with the actual include directory path
# link_directories("/usr/lib/x86_64-linux-gnu/")  # Replace with the actual library directory path



# # Add the Jansson include directories to your project

# project(IALIB)

# set(SOURCE_FILES
#     main.c
#     tools.c
#     cnn_ops.c
# )

# add_executable(${PROJECT_NAME} ${SOURCE_FILES})
# target_link_libraries(${PROJECT_NAME} jansson)

cmake_minimum_required(VERSION 3.14)

project(CNN_INFERENCE)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(googletest/include)

add_executable(test test.c conv.h)

target_link_libraries(test_convlayer gtest gtest_main pthread)