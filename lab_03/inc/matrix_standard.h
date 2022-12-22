//
// Created by dionis on 11.12.22.
//

#ifndef LAB_03_MATRIX_standard_H
#define LAB_03_MATRIX_standard_H


#include <data_types.h>
#include <constants.h>


void init_std_matrix(matrix_std_t *mtr, int rows, int cols);
void convert_from_sparse_form(matrix_sparse_t *src, matrix_std_t *dest);

error_t creat_std_matrix(FILE *file, matrix_std_t *mtr, int total_non_zero_els);
error_t multiply_std(const matrix_std_t *matrix, const matrix_std_t *vector, matrix_std_t *res);


#endif //LAB_03_MATRIX_standard_H
