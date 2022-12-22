//
// Created by dionis on 13.12.22.
//

#ifndef LAB_03_MEASUREMENTS_H
#define LAB_03_MEASUREMENTS_H


#include "data_types.h"


unsigned long long milliseconds_now(void);
void compare_multiplications(void);
long double run_test_std(matrix_std_t *matrix, matrix_std_t *vector);
long double run_test_sparse(matrix_sparse_t *matrix, matrix_sparse_t *vector);


#endif //LAB_03_MEASUREMENTS_H
