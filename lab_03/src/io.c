#include <constants.h>
#include <data_types.h>

void greetings(void)
{
	printf(COLOR_GREEN "%s" COLOR_RESET "%s",
		   "\nHello! With this program you can: \n",
		   " - see the difference in the execution time of different sorting algorithms\n"
		   " - enter your own poster\n"
		   "- delete poster by some field\n"
		   " - sort only the key table, without touching the main one, and see the result\n"
		   " - display sorted table\n"
		   " - sort the key table and use them to display the source table in sorted form\n"
		   " - sort by two different algorithms and display the results\n\n\n");
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


void err_message(const char *message)
{
	printf("%s%s%s", COLOR_RED, message, COLOR_RESET);
}


//void success_message(void)
//{
//	printf(COLOR_GREEN"%s"COLOR_RESET, "\nDONE!\n");
//}
