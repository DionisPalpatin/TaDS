//
// Created by dionis on 11.12.22.
//
#include <assert.h>

#include <io.h>
#include <matrix_sparse.h>
#include <data_types.h>
#include <constants.h>


void init_sparse_matrix(matrix_sparse_t *mtr, int rows, int cols)
{
	assert(mtr);

	mtr->rows = rows;
	mtr->cols = cols;
	mtr->quan = 0;
	memset(mtr->values, 0, MAX_MATRIX_ELEMS * sizeof(int));
	memset(mtr->cols_indexes, 0, MAX_MATRIX_ELEMS * sizeof(int));
	memset(mtr->rows_beginnings, 0, (MAX_MATRIX_SIZE + 1) * sizeof(int));
}


error_t creat_sparse_matrix(FILE *file, matrix_sparse_t *mtr, int total_non_zero_els)
{
	assert(mtr && file);

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
			int new_value = 0;

			if (fscanf(file, "%d%d%d", &row_ind, &col_ind, &new_value) != 3 || row_ind >= mtr->rows || col_ind >= mtr->cols)
			{
				err_message(STANDARD_ERR_MESS);
				exit_code = READ_ERR;
			}
			else if (new_value == 0)
			{
				err_message("You entered zero! Please, enter only non-zero elements.\n");
				i--;
			}
			else
			{
				int index_in_arr = mtr->rows_beginnings[row_ind];
				int next_row_beg = mtr->rows_beginnings[row_ind + 1];
				int cur_col = mtr->cols_indexes[index_in_arr];

				while (index_in_arr < next_row_beg && cur_col < col_ind)
					cur_col = mtr->cols_indexes[++index_in_arr];

				if (mtr->values[index_in_arr] != 0 && next_row_beg > index_in_arr)
				{
					err_message("You have already inputted element in this cell!\n");
					i--;
				}
				else
					ins_elem(mtr, index_in_arr, row_ind, col_ind, new_value);
			}
		}

	return exit_code;
}


void ins_elem(matrix_sparse_t *matrix, int position, int row, int col, int value)
{
	assert(matrix);

	// Сдвигаем все значения
	for (int i = matrix->quan; i > position; --i)
	{
		matrix->values[i] = matrix->values[i - 1];
		matrix->cols_indexes[i] = matrix->cols_indexes[i - 1];
	}
	for (int i = row + 1; i < MAX_MATRIX_SIZE; ++i)
		++(matrix->rows_beginnings[i]);

	// Вставляем элемент
	matrix->values[position] = value;
	matrix->cols_indexes[position] = col;
	++(matrix->quan);
}


error_t multiply_sparse(const matrix_sparse_t *matrix, const matrix_sparse_t *vector, matrix_sparse_t *res)
{
	assert(matrix && vector && res);

	error_t exit_code = OK;

	if (matrix->cols != vector->rows || matrix->cols <= 0 || vector->rows <= 0)
	{
		err_message(MULT_ERR_MESS);
		exit_code = MULT_ERR;
	}

	if (exit_code == OK)
	{
		init_sparse_matrix(res, matrix->rows, vector->cols);

		int ip_res[MAX_MATRIX_SIZE];
		int ip_vector[MAX_MATRIX_SIZE];

		memset(ip_res, 0, MAX_MATRIX_SIZE * sizeof(int));
		memset(ip_vector, 0, MAX_MATRIX_SIZE * sizeof(int));
		for (int i = 0; i < MAX_MATRIX_SIZE; ++i)
			if (vector->rows_beginnings[i] != vector->rows_beginnings[i + 1])
			{
				int pos = vector->rows_beginnings[i];
				ip_vector[i] = vector->values[pos];
			}

		for (int i = 0; i < MAX_MATRIX_SIZE; ++i)
		{
			int row_s = matrix->rows_beginnings[i];
			int row_e = matrix->rows_beginnings[i + 1] - 1;

			for (int j = row_s; j <= row_e; ++j)
				if (ip_vector[matrix->cols_indexes[j]] != 0)
					ip_res[i] += ip_vector[matrix->cols_indexes[j]] * matrix->values[j];
		}

		int total_rows = 0;
		for (int i = 0; i < MAX_MATRIX_SIZE; ++i)
			if (ip_res[i] != 0)
			{
				res->rows_beginnings[i] += total_rows;
				++total_rows;
				res->values[res->rows_beginnings[i]] = ip_res[i];
				++(res->quan);
			}
	}

//	if (exit_code == OK)
//		success_message();

	return exit_code;
}
