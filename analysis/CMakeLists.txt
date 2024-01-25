cmake_minimum_required(VERSION 3.0)

option(DEBUG "Enable debugging" ON)

include_directories("/usr/include")  
link_directories("/usr/lib/x86_64-linux-gnu/")

project(IALIB)

set(SOURCE_FILES
    src/node.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/inc ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(main ${SOURCE_FILES})
