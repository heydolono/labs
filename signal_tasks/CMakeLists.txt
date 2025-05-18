cmake_minimum_required(VERSION 3.14)
project(plotplusplus)

set(CMAKE_CXX_STANDARD 17)

find_package(Python REQUIRED COMPONENTS Development.Module)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(plotplusplus main.cpp plot++.cpp python_interpreter.cpp)

target_link_libraries(plotplusplus PRIVATE ${PYTHON_LIBRARIES})