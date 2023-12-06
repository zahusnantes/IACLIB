cmake_minimum_required(VERSION 3.0)

option(DEBUG "Enable debugging" ON)

include_directories("/usr/include")  
link_directories("/usr/lib/x86_64-linux-gnu/")

project(IALIB)

set(SOURCE_FILES
    tests/test.c
    src/conv.c
    src/pooling.c
    src/max_pooling.c
    src/avg_pooling.c
    src/min_pooling.c
    src/tools.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(test ${SOURCE_FILES})
target_link_libraries(test m)
