
# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(ExampleDLL)

# Set the source file and create the DLL
add_library(ExampleDLL SHARED ExampleDLL.cpp)
