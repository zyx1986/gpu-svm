//
// Created by zhengyuxin on 2/21/17.
//

#ifndef CUDA_SVM_KERNEL_MATRIX_CALCULATION_H
#define CUDA_SVM_KERNEL_MATRIX_CALCULATION_H


#include "svm.h"

void cal_km(struct svm_problem * p_km, svm_problem* prob, svm_parameter* param );


#endif //CUDA_SVM_KERNEL_MATRIX_CALCULATION_H
