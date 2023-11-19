# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProject)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory for header files
include_directories(include)

# Add source files to the project
file(GLOB SOURCES "sources/*.cpp")

# Create an executable
add_executable(MyProject ${SOURCES})

# Link against the C++ Standard Library
target_link_libraries(MyProject PRIVATE stdc++fs)


# CMakeLists.txt

# cmake_minimum_required(VERSION 3.12)
# project(ExampleProject)

# set(CMAKE_CXX_STANDARD 14)

# # Add the source files for the DLL
# add_library(ExampleDLL SHARED ExampleDLL.cpp ExampleDLL.h)

# # Define the export macro for Windows
# if(WIN32)
#     target_compile_definitions(ExampleDLL PRIVATE EXAMPLEDLL_EXPORTS)
# endif()

# # Add the source file for the executable
# add_executable(MainExecutable main_w.cpp)

# # Link the executable with the DLL
# target_link_libraries(MainExecutable PRIVATE ExampleDLL)




# Project/CMakeLists.txt
# CMakeLists.txt in the project root
# CMakeLists.txt
# cmake_minimum_required(VERSION 3.10)

# project(DLLParser)

# add_executable(dll_parser dll_parser.cpp)


