//
// Created by zhengyuxin on 2/23/17.
//

#ifndef CUDA_SVM_GRID_H
#define CUDA_SVM_GRID_H


#include "svm.h"

svm_parameter* get_best_parameter_set_from_cross_validation(
        svm_problem* prob, svm_parameter** param, int nr_fold, int num_parameter_sets );


#endif //CUDA_SVM_GRID_H
