//
// Created by dionis on 11.12.22.
//
#include <assert.h>

#include <io.h>
#include <matrix_standard.h>
#include <data_types.h>
#include <constants.h>


void init_std_matrix(matrix_std_t *mtr, int rows, int cols)
{
	assert(mtr);

	mtr->rows = rows;
	mtr->cols = cols;

	memset(mtr->data, 0, MAX_MATRIX_SIZE * MAX_MATRIX_SIZE * sizeof(int));
}


void convert_from_sparse_form(matrix_sparse_t *src, matrix_std_t *dest)
{
	assert(src && dest);

	init_std_matrix(dest, src->rows, src->cols);
	for (int i = 0; i < src->rows; ++i)
		for (int j = src->rows_beginnings[i]; j < src->rows_beginnings[i + 1]; ++j)
			dest->data[i][src->cols_indexes[j]] = src->values[j];
}


error_t creat_std_matrix(FILE *file, matrix_std_t *mtr, int total_non_zero_els)
{
	assert(file && mtr);

	error_t exit_code = OK;

	if (total_non_zero_els <= 0 || total_non_zero_els > MAX_MATRIX_ELEMS)
	{
		err_message(NON_ZERO_QUAN_ERR_MESS);
		exit_code = NON_ZERO_QUAN_ERR;
	}
	else
		for (int i = 0; i < total_non_zero_els && exit_code == OK; ++i)
		{
			int row_ind = 0, col_ind = 0;
			int new_values = 0;

			if (fscanf(file, "%d%d%d", &row_ind, &col_ind, &new_values) != 3 || row_ind >= mtr->rows || col_ind >= mtr->cols)
			{
				err_message(STANDARD_ERR_MESS);
				exit_code = READ_ERR;
			}

			if (exit_code == OK)
				mtr->data[row_ind][col_ind] = new_values;
		}

	return exit_code;
}


error_t multiply_std(const matrix_std_t *matrix, const matrix_std_t *vector, matrix_std_t *res)
{
	assert(matrix && vector && res);

	error_t exit_code = OK;

	if (matrix->cols != vector->rows || matrix->cols == -1 || vector->rows == -1)
	{
		err_message(MULT_ERR_MESS);
		exit_code = MULT_ERR;
	}
	else
	{
		init_std_matrix(res, matrix->rows, 1);

		for (int i = 0; i < matrix->rows; ++i)
			for (int j = 0; j < matrix->cols; ++j)
				res->data[i][0] += matrix->data[i][j] * vector->data[j][0];
	}

//	if (exit_code == OK)
//		success_message();

	return exit_code;
}
