
#include <printf.h>
#include <stdlib.h>
#include <stdio.h>
#include "Global.h"
#include "cross_validation_with_matrix_precomputation.h"
#include "kernel_matrix_calculation.h"

void setup_pkm(struct svm_problem *p_km, svm_problem* prob)
{
	int i;

	p_km->l = prob->l;
	p_km->x = Malloc(struct svm_node,p_km->l);
	p_km->y = Malloc(double,p_km->l);

	for(i=0;i<prob->l;i++)
	{
		(p_km->x+i)->values = Malloc(double,prob->l+1);
		(p_km->x+i)->dim = prob->l+1;
	}

	for( i=0; i<prob->l; i++) p_km->y[i] = prob->y[i];
}



void free_pkm(struct svm_problem *p_km, svm_problem* prob)
{
	int i;

	for(i=0; i < prob->l; i++)
		free( (p_km->x+i)->values);

	free( p_km->x );
	free( p_km->y );

}

void free_problem( svm_problem *p_km )
{
    int i;

    for(i=0; i < p_km->l; i++)
        free( (p_km->x+i)->values);

    free( p_km->x );
    free( p_km->y );
}


double do_crossvalidation(struct svm_problem * p_km, svm_problem* prob, svm_parameter* param, int nr_fold)
{
			double rate;

			int i;
			int total_correct = 0;
			double total_error = 0;
			double sumv = 0, sumy = 0, sumvv = 0, sumyy = 0, sumvy = 0;
			double *target = Malloc(double,prob->l);

			svm_cross_validation(p_km, param, nr_fold, target);


			if(param->svm_type == EPSILON_SVR ||
				param->svm_type == NU_SVR)
			{
				for(i=0;i<prob->l;i++)
				{
					double y = prob->y[i];
					double v = target[i];
					total_error += (v-y)*(v-y);
					sumv += v;
					sumy += y;
					sumvv += v*v;
					sumyy += y*y;
					sumvy += v*y;
				}
				printf("Cross Validation Mean squared error = %g\n",total_error/prob->l);
				printf("Cross Validation Squared correlation coefficient = %g\n",
								((prob->l*sumvy-sumv*sumy)*(prob->l*sumvy-sumv*sumy))/
								((prob->l*sumvv-sumv*sumv)*(prob->l*sumyy-sumy*sumy))
								);
			}
			else
			{
				for(i=0;i<prob->l;i++)
					if(target[i] == prob->y[i])
						++total_correct;

				rate = (100.0*total_correct)/prob->l;


			}
			free(target);

			
			return rate;

}

double run_pair(struct svm_problem * p_km, svm_problem* prob, svm_parameter* param, int nr_fold  )
{

	double rate;

	cal_km( p_km, prob, param );

	int original_kernel_type = param->kernel_type;

	param->kernel_type = PRECOMPUTED;

	rate = do_crossvalidation(p_km, prob, param, nr_fold);

	printf("Cross Validation = %g%%\n", rate);

	param->kernel_type = original_kernel_type;

	return rate;

}



double do_cross_validation_with_KM_precalculated( svm_problem* prob, svm_parameter* param, int nr_fold )
{
    struct svm_problem p_km;

    setup_pkm(&p_km, prob);

	double rate = run_pair(&p_km, prob, param, nr_fold);

    free_problem(&p_km);

	return rate;
}