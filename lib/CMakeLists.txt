cmake_minimum_required(VERSION 3.0)

option(DEBUG "Enable debugging" ON)

include_directories("/usr/include")  
link_directories("/usr/lib/x86_64-linux-gnu/")

project(IALIB)

set(SOURCE_FILES
    tests/mnist_dataset/test_mnist.cpp
    tests/mnist_dataset/read_mnist.cpp
    src/conv.c
    src/fc.c
    src/pooling.c
    src/tools.c
    src/inference.c
    src/activation.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(test ${SOURCE_FILES})
target_link_libraries(test m z)

# cmake_minimum_required(VERSION 3.0)

# option(DEBUG "Enable debugging" ON)

# include_directories("/usr/include")
# link_directories("/usr/lib/x86_64-linux-gnu/")

# set(GTEST_DIR googletest)

# project(IALIB)

# set(SOURCE_FILES
#     src/conv.c
#     src/fc.c
#     src/pooling.c
#     src/tools.c
#     src/inference.c
#     src/activation.c
#     tests/test_tools.cpp
#     tests/test_main.cpp
# )

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc ${GTEST_DIR}/include)
# link_directories(${GTEST_DIR}/lib)

# add_executable(test ${SOURCE_FILES})

# target_link_libraries(test m gtest gtest_main)