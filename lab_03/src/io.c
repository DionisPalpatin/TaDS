#include <constants.h>
#include <data_types.h>

void greetings(void)
{
	printf(COLOR_GREEN "\nHello!\n" COLOR_RESET);
}


void print_menu(void)
{
	printf(COLOR_BLUE"%s" COLOR_RESET "%s",
		   "\n\nMENU (select one item, enter a number):\n\n",
		   " 1 - Filling in a matrix from a file;\n"
		   " 2 - Filling in the matrix manually;\n"
		   " 3 - Filling in a vector from a file;\n"
		   " 4 - Filling in the vector manually;\n"
		   " 5 - Multi of a classical matrix on a vector;\n"
		   " 6 - Multi of a special storage method matrix by a vector;\n"
		   " 7 - The output of the comparison time works;\n"
		   " 8 - Output multiplication results in standard format.\n"
		   " 9 - Output multiplication results in sparse format.\n"
		   "10 - Output multiplication results in coordinate format\n"
		   "11 - Output the vector in standard format.\n"
		   "12 - Output the vector in sparse form.\n"
		   "13 - Output the vector in coordinate format.\n"
		   "14 - Output the matrix in standard format.\n"
		   "15 - Output the matrix in sparse form.\n"
		   "16 - Output the matrix in coordinate format.\n"
		   "17 - Menu.\n"
		   " 0 - Program exit.\n"
	);
}


void input_prompt(void)
{
	printf(COLOR_BLUE"%s"COLOR_RESET"%s","\n\nEnter 17 to display the menu", "\nEnter your choice: ");
}


void print_coord_format(const matrix_std_t *matrix)
{
    if (matrix->rows == 0)
    {
        printf("Matrix is empty.\n");
        return;
    }

    printf(" i   j   value\n\n");
	int non_zero_els = 0;
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->cols; j++)
            if (matrix->data[i][j] != 0)
			{
				printf("%3d %3d %5d\n", i, j, matrix->data[i][j]);
				++non_zero_els;
			}

    if (non_zero_els + 1 == 0)
        printf("All elements are equal to zero!\n\n");
}


void print_std_format(const matrix_std_t *matrix)
{
    if (matrix->rows == 0)
    {
        printf("Matrix or vector is empty.\n");
        return;
    }

    if (matrix->cols > 50 || matrix->rows > 50)
    {
        printf("The matrix is too large. It is not possible to display it in its entirety.\n"
			   "Use coordinate format instead.\n");
        return;
    }

	for (int i = 0; i < matrix->rows; ++i)
	{
		int j = 0;
		for (; j < matrix->cols - 1; ++j)
			printf("%d ", matrix->data[i][j]);
		printf("%d\n", matrix->data[i][j]);
	}
	printf("\n\n\n");
}


void print_sparse_format(matrix_sparse_t *const matrix)
{

    if (matrix->quan == 0)
    {
        printf("Matrix is empty.\n");
        return;
    }

	int i;

	printf("Array of values: ");
    for (i = 0; i < matrix->quan - 1; ++i)
		printf("%d ", matrix->values[i]);
	printf("%d\n", matrix->values[i]);

	printf("Array of columns indexes: ");
	for (i = 0; i < matrix->quan - 1; ++i)
		printf("%d ", matrix->cols_indexes[i]);
	printf("%d\n", matrix->cols_indexes[i]);

	printf("Array of pointers to rows beginnings: ");
	for (i = 0; i < matrix->rows - 1; ++i)
		printf("%d ", matrix->rows_beginnings[i]);
	printf("%d", matrix->rows_beginnings[i]);
}


void print_meas_results_tables(long double results[8][9], double *pers)
{
	printf("|---------------|----------|---------------------------------------------------|---------------------------------------------------|\n"
		   "|   Sparsity    |          |            Standard matrix and vector             |             Sparse matrix and vector              |\n"
		   "|    factor     |   What   |------------|------------|------------|------------|------------|------------|------------|------------|\n"
		   "|               |          |   10x10    |   50x50    |  100x100   |  150x150   |   10x10    |   50x50    |  100x100   |  150x150   |\n"
		   "|---------------|----------|------------|------------|------------|------------|------------|------------|------------|------------|\n");

	for (int i = 0; i < 9; ++i)
	{
		printf("|               |Time (ms) |%12Lf|%12Lf|%12Lf|%12Lf|%12Lf|%12Lf|%12Lf|%12Lf|\n",
			   results[0][i], results[1][i], results[2][i], results[3][i], results[4][i], results[5][i], results[6][i], results[7][i]);
		printf("|%15d|----------|------------|------------|------------|------------|------------|------------|------------|------------|\n", (int)(pers[i] * 100));
		printf("|               |Memory(b) |%12zu|%12zu|%12zu|%12zu|%12zu|%12zu|%12zu|%12zu|\n",
			   sizeof(matrix_std_t), sizeof(matrix_std_t), sizeof(matrix_std_t), sizeof(matrix_std_t),
			   sizeof(matrix_sparse_t), sizeof(matrix_sparse_t), sizeof(matrix_sparse_t), sizeof(matrix_sparse_t));
		printf("|---------------|----------|------------|------------|------------|------------|------------|------------|------------|------------|\n");
	}

	printf("\n\n\n");
	printf("|---------------|--------------|---------------------------------------------------|\n"
		   "|   Sparsity    |              |            Ratio std matrix to sparse             |\n"
		   "|    factor     |     What     |------------|------------|------------|------------|\n"
		   "|               |              |   10x10    |   50x50    |  100x100   |  150x150   |\n"
		   "|---------------|--------------|------------|------------|------------|------------|\n");

	for (int i = 0; i < 9; ++i)
	{
		printf("|               |  Time ratio  |%12Lf|%12Lf|%12Lf|%12Lf|\n",
			   results[0][i] / results[4][i],
			   results[1][i] / results[5][i],
			   results[2][i] / results[6][i],
			   results[3][i] / results[7][i]);
		printf("|%15d|--------------|------------|------------|------------|------------|\n", (int)(pers[i] * 100));
		printf("|               | Memory ratio |%12lf|%12lf|%12lf|%12lf|\n",
			   (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t),
			   (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t),
			   (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t),
			   (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t));
		printf("|---------------|--------------|------------|------------|------------|------------|\n");
	}
}


void print_meas_results_tables_to_file(long double results[8][9])
{
	FILE *out_f = fopen("res_file_format.txt", "w");
	if (!out_f)
		return;

	for (int i = 0; i < 9; ++i)
	{
		fprintf(out_f, "%12Lf %12Lf %12Lf %12Lf %12Lf %12Lf %12Lf %12Lf\n",
				results[0][i], results[1][i], results[2][i], results[3][i], results[4][i], results[5][i], results[6][i], results[7][i]);
		fprintf(out_f, "%12zu %12zu %12zu %12zu %12zu %12zu %12zu %12zu\n",
			    sizeof(matrix_std_t), sizeof(matrix_std_t), sizeof(matrix_std_t), sizeof(matrix_std_t),
			    sizeof(matrix_sparse_t), sizeof(matrix_sparse_t), sizeof(matrix_sparse_t), sizeof(matrix_sparse_t));
	}

	printf("\n\n\n");

	for (int i = 0; i < 9; ++i)
	{
		fprintf(out_f, "%12Lf %12Lf %12Lf %12Lf\n",
				results[0][i] / results[4][i],
				results[1][i] / results[5][i],
				results[2][i] / results[6][i],
				results[3][i] / results[7][i]);
		fprintf(out_f, "%12lf %12lf %12lf %12lf\n",
			    (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t),
			    (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t),
			    (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t),
			    (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t));
	}

	fclose(out_f);
}



void err_message(const char *message)
{
	printf("%s%s%s", COLOR_RED, message, COLOR_RESET);
}
