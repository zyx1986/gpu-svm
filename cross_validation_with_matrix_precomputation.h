//
// Created by zhengyuxin on 2/21/17.
//

#ifndef CUDA_SVM_CROSS_VALIDATION_WITH_MATRIX_PRECOMPUTATION_H
#define CUDA_SVM_CROSS_VALIDATION_WITH_MATRIX_PRECOMPUTATION_H

#include "svm.h"


double do_cross_validation_with_KM_precalculated( svm_problem* prob, svm_parameter* param, int nr_fold );

#endif //CUDA_SVM_CROSS_VALIDATION_WITH_MATRIX_PRECOMPUTATION_H
