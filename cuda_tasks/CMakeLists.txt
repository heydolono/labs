cmake_minimum_required(VERSION 3.18)
project(cuda_tasks LANGUAGES CUDA CXX)

set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

add_executable(task_01_vector_add task_01_vector_add.cu)
add_executable(task_02_function task_02_function.cu)
add_executable(task_03_slae task_03_slae.cu)
add_executable(task_04_matrix_mul task_04_matrix_mul.cu)
add_executable(task_05_array_processing task_05_array_processing.cu)