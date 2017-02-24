cmake_minimum_required(VERSION 3.6)
project(cuda_svm)

set(CMAKE_CXX_STANDARD 11)

find_package(CUDA QUIET REQUIRED)

set(SOURCE_FILES
        svm.h
        svm.cpp
        cross_validation_with_matrix_precomputation.h
        cross_validation_with_matrix_precomputation.cu
        kernel_matrix_calculation.h
        kernel_matrix_calculation.cu
        Global.h
        grid.h
        grid.cpp)


cuda_add_executable(cuda_svm ${SOURCE_FILES} svm-train.c )
cuda_add_executable(cuda_svm_1 ${SOURCE_FILES} main.cpp )

cuda_add_cublas_to_target( cuda_svm )
cuda_add_cublas_to_target( cuda_svm_1 )