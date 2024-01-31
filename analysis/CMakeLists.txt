cmake_minimum_required(VERSION 3.0)

option(DEBUG "Enable debugging" ON)

project(IALIB_ANALYZER)

set(SOURCE_FILES
    src/node.cpp
    src/main.cpp
    ../lib/src/tools.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/inc ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(main ${SOURCE_FILES})

target_link_libraries(main yaml-cpp)