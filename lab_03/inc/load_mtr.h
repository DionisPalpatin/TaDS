//
// Created by dionis on 11.12.22.
//

#ifndef LAB_03_LOAD_MTR_H
#define LAB_03_LOAD_MTR_H


#include <data_types.h>
#include <constants.h>


error_t load_mtr_for_test(const char *filename, int non_z, matrix_sparse_t *mtr_sparse, matrix_std_t *mtr_std);
error_t load_mtr_from_file(matrix_sparse_t *mtr_sparse, matrix_std_t *mtr_std);
error_t load_mtr_from_cons(matrix_sparse_t *mtr_sparse, matrix_std_t *mtr_std);
error_t load_vector_from_file(matrix_sparse_t *vector_sparse, matrix_std_t *vector_std);
error_t load_vector_from_cons(matrix_sparse_t *vector_sparse, matrix_std_t *vector_std);


#endif //LAB_03_LOAD_MTR_H
