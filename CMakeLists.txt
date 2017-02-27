cmake_minimum_required(VERSION 3.6)
project(cuda_svm)

set(CMAKE_CXX_STANDARD 11)

find_package(CUDA QUIET REQUIRED)

set(SOURCE_FILES
        svm.h
        svm.cpp
        Global.h
        )


#add_compile_options(-D_DENSE_REP)

cuda_add_executable(svm_train
        ${SOURCE_FILES}
        cross_validation_with_matrix_precomputation.h
        cross_validation_with_matrix_precomputation.cpp
        kernel_matrix_calculation.h
        kernel_matrix_calculation.cpp
        grid.h
        grid.cpp
        svm-train.cpp)


add_executable(svm_scale
        svm-scale.cpp)

add_executable(svm_predict
        ${SOURCE_FILES}
        svm-predict.cpp)

add_executable(svm_test main.cpp )


target_compile_definitions(svm_train PUBLIC _DENSE_REP=1)
cuda_add_cublas_to_target( svm_train )





