# cmake_minimum_required(VERSION 3.0)

# option(DEBUG "Enable debugging" ON)

# include_directories("/usr/include")  
# link_directories("/usr/lib/x86_64-linux-gnu/")

# project(IALIB)

# set(SOURCE_FILES
#     # tests/test_mnist.c
#     # tests/read_mnist.c
#     tests/test.c
#     src/conv.c
#     src/fc.c
#     src/pooling.c
#     src/max_pooling.c
#     src/avg_pooling.c
#     src/min_pooling.c
#     src/tools.c
#     src/inference.c
#     src/activation.c
# )

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# add_executable(test ${SOURCE_FILES})
# target_link_libraries(test m z)

cmake_minimum_required(VERSION 3.0)

option(DEBUG "Enable debugging" ON)

include_directories("/usr/include")
link_directories("/usr/lib/x86_64-linux-gnu/")

set(GTEST_DIR googletest)

project(IALIB)

set(SOURCE_FILES
    src/conv.c
    src/fc.c
    src/pooling.c
    src/max_pooling.c
    src/avg_pooling.c
    src/min_pooling.c
    src/tools.c
    src/inference.c
    src/activation.c
    tests/test_conv.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc ${GTEST_DIR}/include)
link_directories(${GTEST_DIR}/lib)

add_executable(test ${SOURCE_FILES})

target_link_libraries(test m gtest gtest_main)

