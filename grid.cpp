//
// Created by zhengyuxin on 2/23/17.
//
#include "grid.h"
#include "cross_validation_with_matrix_precomputation.h"
#include <algorithm>



// return the best svm parameter
svm_parameter* get_best_parameter_set_from_cross_validation(
        svm_problem* prob, svm_parameter* param, int nr_fold, int num_parameter_sets ) {
    double best_rate = -1;
    int best_rate_index = -1;
    for (int i = 0; i < num_parameter_sets; i++) {
        double rate = do_cross_validation_with_KM_precalculated(prob, &(param[i]), nr_fold);

        if (best_rate < rate) {
            best_rate = rate;
            best_rate_index = i;
        }
    }

    return &param[best_rate_index];
}



/**
 * two parameters are needed: c and gamma
 *
 */
std::pair<svm_parameter*, int> set_parameters(
        svm_parameter *param,
        double log_c_min, double log_c_max, double log_c_step,
        double log_g_min, double log_g_max, double log_g_step)
{
    int num_c_values = (int) std::max( 1.0, (log_c_max - log_c_min) / log_c_step );
    int num_g_values = (int) std::max( 1.0, (log_g_max - log_g_min) / log_g_step );
    int num_parameter_sets = num_c_values * num_g_values;

    svm_parameter* returned_parameter_set = new svm_parameter[num_parameter_sets];

    for ( int i = 0; i < num_c_values; i++ )
    {
        for ( int j = 0; j < num_g_values; j++ )
        {
            returned_parameter_set[i * num_c_values + j] =
                    copy_existing_parameter( param );
            returned_parameter_set[i * num_c_values + j].C =
                    std::pow( 2, log_c_min + log_c_step * i );
            returned_parameter_set[i * num_c_values + j].gamma =
                    std::pow( 2, log_g_min + log_g_step * j );
        }
    }

    return std::make_pair( returned_parameter_set, num_parameter_sets );
}



