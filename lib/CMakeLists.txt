cmake_minimum_required(VERSION 3.0)

option(DEBUG "Enable debugging" ON)

include_directories("/usr/include")  
link_directories("/usr/lib/x86_64-linux-gnu/")

project(IALIB)

set(SOURCE_FILES
    tests/test.c
    src/tools.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(test ${SOURCE_FILES})
