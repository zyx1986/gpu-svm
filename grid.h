//
// Created by zhengyuxin on 2/23/17.
//

#ifndef CUDA_SVM_GRID_H
#define CUDA_SVM_GRID_H


#include <utility>
#include "svm.h"

svm_parameter* get_best_parameter_set_from_cross_validation(
        svm_problem* prob, svm_parameter** param, int nr_fold, int num_parameter_sets );


std::pair<svm_parameter*, int> set_parameters(
        svm_parameter *param,
        double log_c_min, double log_c_max, double log_c_step,
        double log_g_min, double log_g_max, double log_g_step);

#endif //CUDA_SVM_GRID_H
