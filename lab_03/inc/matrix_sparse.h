//
// Created by dionis on 11.12.22.
//

#ifndef LAB_03_MATRIX_SPARSE_H
#define LAB_03_MATRIX_SPARSE_H


#include <data_types.h>
#include <constants.h>


error_t creat_sparse_matrix(FILE *file, matrix_sparse_t *mtr, int total_non_zero_els);
error_t multiply_sparse(const matrix_sparse_t *matrix, const matrix_sparse_t *vector, matrix_sparse_t *res);

void init_sparse_matrix(matrix_sparse_t *mtr, int rows, int cols);
void ins_elem(matrix_sparse_t *matrix, int i, int j, int val);


#endif //LAB_03_MATRIX_SPARSE_H
