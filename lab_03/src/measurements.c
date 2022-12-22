//
// Created by dionis on 13.12.22.
//
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "measurements.h"
#include <data_types.h>
#include <matrix_sparse.h>
#include <matrix_standard.h>
#include <load_mtr.h>


unsigned long long milliseconds_now(void)
{
	struct timeval val;

	if (gettimeofday(&val, NULL))
		return (unsigned long long) -1;

	return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}


void compare_multiplications(void)
{
	matrix_std_t mtr_std;
	matrix_std_t vector_std;
	matrix_sparse_t mtr_sparse;
	matrix_sparse_t vector_sparse;

	int sizes[] = {10, 50, 100, 150};
	double pers[] = {0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5};
	long double results[8][9];

	// Производим замеры
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 9; ++j)
		{
//			printf("%d %lf\n", sizes[i], pers[j]);
			char mtr_file_name[1001], vec_file_name[1001];
			snprintf(mtr_file_name, 1001, MTR_FILE_FORMAT_LINE, sizes[i], (int)(pers[j] * 100));
			snprintf(vec_file_name, 1001, VEC_FILE_FORMAT_LINE, sizes[i], (int)(pers[j] * 100));

			init_sparse_matrix(&mtr_sparse, sizes[i], sizes[i]);
			(void) load_mtr_for_test(mtr_file_name, (int)(pers[j] * sizes[i] * sizes[i]), &mtr_sparse, &mtr_std);

			init_sparse_matrix(&vector_sparse, sizes[i], 1);
			(void) load_mtr_for_test(vec_file_name, (int)(pers[j] * sizes[i]), &vector_sparse, &vector_std);

			results[i][j] = run_test_std(&mtr_std, &vector_std);
			results[i + 4][j] = run_test_sparse(&mtr_sparse, &vector_sparse);
		}


	// Выводим результат
	printf("|---------------|----------|---------------------------------------------------|---------------------------------------------------|\n"
		   "|   Sparcity    |          |            Standard matrix and vector             |             Sparse matrix and vector              |\n"
		   "|    factor     |   What   |------------|------------|------------|------------|------------|------------|------------|------------|\n"
		   "|               |          |   10x10    |   50x50    |  100x100   |  150x150   |   10x10    |   50x50    |  100x100   |  150x150   |\n"
		   "|---------------|----------|------------|------------|------------|------------|------------|------------|------------|------------|\n");

	for (int i = 0; i < 9; ++i)
	{
		printf("|               |Memory(b) |%12zu|%12zu|%12zu|%12zu|%12zu|%12zu|%12zu|%12zu|\n",
			   sizeof(matrix_std_t), sizeof(matrix_std_t), sizeof(matrix_std_t), sizeof(matrix_std_t),
			   sizeof(matrix_sparse_t), sizeof(matrix_sparse_t), sizeof(matrix_sparse_t), sizeof(matrix_sparse_t));
		printf("|%15d|----------|------------|------------|------------|------------|------------|------------|------------|------------|\n", (int)(pers[i] * 100));
		printf("|               |Time (ms) |%12Lf|%12Lf|%12Lf|%12Lf|%12Lf|%12Lf|%12Lf|%12Lf|\n",
			   results[0][i], results[1][i], results[2][i], results[3][i], results[4][i], results[5][i], results[6][i], results[7][i]);
		printf("|---------------|----------|------------|------------|------------|------------|------------|------------|------------|------------|\n");
	}

	printf("\n\n\n");
	printf("|---------------|----------|---------------------------------------------------|\n"
		   "|   Sparcity    |          |            Standard matrix and vector             |\n"
		   "|    factor     |   What   |------------|------------|------------|------------|\n"
		   "|               |          |   10x10    |   50x50    |  100x100   |  150x150   |\n"
		   "|---------------|----------|------------|------------|------------|------------|\n");

	for (int i = 0; i < 9; ++i)
	{
		printf("|               |Memory(b) |%12lf|%12lf|%12lf|%12lf|\n",
			   (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t),
			   (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t),
			   (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t),
			   (double)sizeof(matrix_std_t) / sizeof(matrix_sparse_t));
		printf("|%15d|----------|------------|------------|------------|------------|\n", (int)(pers[i] * 100));
		printf("|               |Time (ms) |%12Lf|%12Lf|%12Lf|%12Lf|\n",
			   results[0][i] / results[4][i],
			   results[1][i] / results[5][i],
			   results[2][i] / results[6][i],
			   results[3][i] / results[7][i]);
		printf("|---------------|----------|------------|------------|------------|------------|\n");
	}
}


long double run_test_std(matrix_std_t *matrix, matrix_std_t *vector)
{
	matrix_std_t res;
	long long unsigned time_start, time_end;
	long double time_res = 0;

	for (int i = 0; i < TOTAL_TEST_RUNS; ++i)
	{
		time_start = milliseconds_now();
		(void) multiply_std(matrix, vector, &res);
		time_end = milliseconds_now();

		time_res += time_end - time_start;
	}

	return time_res / TOTAL_TEST_RUNS;
}


long double run_test_sparse(matrix_sparse_t *matrix, matrix_sparse_t *vector)
{
	matrix_sparse_t res;
	long long unsigned time_start, time_end;
	long double time_res = 0;

	for (int i = 0; i < TOTAL_TEST_RUNS; ++i)
	{
		time_start = milliseconds_now();
		(void) multiply_sparse(matrix, vector, &res);
		time_end = milliseconds_now();

		time_res += time_end - time_start;
	}

	return time_res / TOTAL_TEST_RUNS;
}
