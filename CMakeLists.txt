cmake_minimum_required(VERSION 3.18)
project(lookup-table-example)
add_executable(sketch examples/sketch.cpp)
set_target_properties(sketch PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED TRUE)
target_include_directories(sketch PRIVATE include)
