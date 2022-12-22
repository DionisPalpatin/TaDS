//
// Created by dionis on 11.12.22.
//
#include <assert.h>

#include <load_mtr.h>
#include <data_types.h>
#include <constants.h>
#include <io.h>
#include <matrix_sparse.h>
#include <matrix_standard.h>


error_t load_mtr_for_test(const char *filename, int non_z, matrix_sparse_t *mtr_sparse, matrix_std_t *mtr_std)
{
	assert(filename && mtr_sparse && mtr_std);

	error_t exit_code = OK;

	FILE *src = fopen(filename, "r");
	if (!src)
	{
		err_message(FILE_ERR_MESS);
		exit_code = FILE_ERR;
	}

	if (exit_code == OK)
	{
		init_sparse_matrix(mtr_sparse, mtr_sparse->rows, mtr_sparse->cols);
		exit_code = creat_sparse_matrix(src, mtr_sparse, non_z);
	}

	if (exit_code == OK)
		convert_from_sparse_form(mtr_sparse, mtr_std);

//	if (exit_code == OK)
//		success_message();

	return exit_code;
}


error_t load_mtr_from_file(matrix_sparse_t *mtr_sparse, matrix_std_t *mtr_std)
{
	assert(mtr_sparse && mtr_std);

	error_t exit_code = OK;

	int choice = 0;
	printf("Select the matrix size:\n"
		   "1 - 10x10;\n"
		   "2 - 50x50;\n"
		   "3 - 100x100;\n"
		   "4 - 150x150\n\n"
		   "INPUT:");
	if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4)
	{
		err_message(CHOICE_ERR_MESS);
		exit_code = CHOICE_ERR;
	}

	int matrix_size = 0;
	if (exit_code == OK)
	{
		if (choice == 1)
			matrix_size = 10;
		else if (choice == 2)
			matrix_size = 50;
		else if (choice == 3)
			matrix_size = 100;
		else
			matrix_size = 150;
	}

	if (exit_code == OK)
	{
		printf("Enter the percentage of table completion: (0%%..100%%) ");
		if (scanf("%d", &choice) != 1 || choice < 0 || choice > 100)
		{
			err_message(CHOICE_ERR_MESS);
			exit_code = CHOICE_ERR;
		}
	}

	FILE *src = NULL;
	if (exit_code == OK)
	{
		char file_name[1001];
		snprintf(file_name, 1001, MTR_FILE_FORMAT_LINE, matrix_size, choice);
		src = fopen(file_name, "r");
		if (!src)
			exit_code = FILE_ERR;
	}

	if (exit_code == OK)
	{
		init_sparse_matrix(mtr_sparse, matrix_size, matrix_size);
		int non_zero_els = (int)(matrix_size * matrix_size * choice / 100.0);
		exit_code = creat_sparse_matrix(src, mtr_sparse, non_zero_els);
	}

	if (exit_code == OK)
		convert_from_sparse_form(mtr_sparse, mtr_std);

//	if (exit_code == OK)
//		success_message();

	return exit_code;
}


error_t load_mtr_from_cons(matrix_sparse_t *mtr_sparse, matrix_std_t *mtr_std)
{
	assert(mtr_sparse && mtr_std);

	error_t exit_code = OK;

	printf("Enter the dimensions of the matrix\n"
		   "(separated by a space, each size from 1 to 150)\nINPUT: ");
	int rows = 0, cols = 0;
	if (scanf("%d%d", &rows, &cols) != 2 ||
			rows <= 0 || rows > MAX_MATRIX_SIZE ||
			cols <= 0 || cols > MAX_MATRIX_SIZE)
	{
		err_message(MTR_SIZE_ERR_MESS);
		exit_code = MTR_SIZE_ERR;
	}

	printf("Enter the number of non-zero matrix elements.\nINPUT: ");
	int non_zeros = 0;
	if (scanf("%d", &non_zeros) != 1 || non_zeros > rows * cols || non_zeros <= 0)
	{
		err_message(NON_ZERO_QUAN_ERR_MESS);
		exit_code = NON_ZERO_QUAN_ERR;
	}

	if (exit_code == OK)
	{
		printf(COLOR_GREEN
				"ATTENTION\n"
				COLOR_RESET
				"Entering %d elements according to the scheme (ROW COLUMN ELEMENT)\n",
			   	non_zeros);
		init_sparse_matrix(mtr_sparse, rows, cols);
		exit_code = creat_sparse_matrix(stdin, mtr_sparse, non_zeros);
	}

	if (exit_code == OK)
		convert_from_sparse_form(mtr_sparse, mtr_std);

//	if (exit_code == OK)
//		success_message();

	return exit_code;
}


error_t load_vector_from_file(matrix_sparse_t *vector_sparse, matrix_std_t *vector_std)
{
	assert(vector_sparse && vector_std);

	error_t exit_code = OK;

	int choice = 0;
	printf("Select the matrix size:\n"
		   "1 - 10x1;\n"
		   "2 - 50x1;\n"
		   "3 - 100x1;\n"
		   "4 - 150x1\n\n"
		   "INPUT:");
	if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4)
	{
		err_message(CHOICE_ERR_MESS);
		exit_code = CHOICE_ERR;
	}

	int vector_size = 0;
	if (exit_code == OK)
	{
		if (choice == 1)
			vector_size = 10;
		else if (choice == 2)
			vector_size = 50;
		else if (choice == 3)
			vector_size = 100;
		else
			vector_size = 150;
	}

	if (exit_code == OK)
	{
		printf("Enter the percentage of table completion: (0%%..100%%) ");
		if (scanf("%d", &choice) != 1 || choice < 0 || choice > 100)
		{
			err_message(CHOICE_ERR_MESS);
			exit_code = CHOICE_ERR;
		}
	}

	FILE *src = NULL;
	if (exit_code == OK)
	{
		char file_name[1001];
		snprintf(file_name, 1001, VEC_FILE_FORMAT_LINE, vector_size, choice);
		src = fopen(file_name, "r");
		if (!src)
			exit_code = FILE_ERR;
	}

	if (exit_code == OK)
	{
		init_sparse_matrix(vector_sparse, vector_size, 1);
		int non_zero_els = (int)(vector_size * choice / 100.0);
		exit_code = creat_sparse_matrix(src, vector_sparse, non_zero_els);
	}

	if (exit_code == OK)
		convert_from_sparse_form(vector_sparse, vector_std);

//	if (exit_code == OK)
//		success_message();

	return exit_code;
}


error_t load_vector_from_cons(matrix_sparse_t *vector_sparse, matrix_std_t *vector_std)
{
	assert(vector_sparse && vector_std);

	error_t exit_code = OK;

	printf("Enter the dimensions of the vector\n"
		   "(from 1 to 150)\nINPUT: ");
	int rows = 0;
	if (scanf("%d", &rows) != 1 ||
		rows <= 0 || rows > MAX_MATRIX_SIZE)
	{
		err_message(MTR_SIZE_ERR_MESS);
		exit_code = MTR_SIZE_ERR;
	}

	printf("Enter the number of non-zero matrix elements.\nINPUT: ");
	int non_zeros = 0;
	if (scanf("%d", &non_zeros) != 1 || non_zeros > rows || non_zeros <= 0)
	{
		err_message(NON_ZERO_QUAN_ERR_MESS);
		exit_code = NON_ZERO_QUAN_ERR;
	}

	if (exit_code == OK)
	{
		printf(COLOR_GREEN
			   "ATTENTION\n"
			   COLOR_RESET
			   "Entering %d elements according to the scheme (ROW COLUMN ELEMENT)\n",
			   non_zeros);
		init_sparse_matrix(vector_sparse, rows, 1);
		exit_code = creat_sparse_matrix(stdin, vector_sparse, non_zeros);
	}

	if (exit_code == OK)
		convert_from_sparse_form(vector_sparse, vector_std);

//	if (exit_code == OK)
//		success_message();

	return exit_code;
}
