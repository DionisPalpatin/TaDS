//
// Created by dionis on 13.12.22.
//
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <measurements.h>
#include <data_types.h>
#include <graph.h>
#include <constants.h>
#include <io.h>


unsigned long long milliseconds_now(void)
{
	struct timeval val;

	if (gettimeofday(&val, NULL))
		return (unsigned long long) -1;

	return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}


void compare_realizations(int print_to_console)
{
	road_graph_t graph_matrix = {.total_cities = 0, .roads_matrix = NULL};
	road_graph_list_t graph_list = {.total_cities = 0, .cities = NULL};

	long double results[10][2];
	size_t sizes[10][2];

	// Производим замеры
	for (int i = 0; i < 10; ++i)
	{
		char src_file_name[1001];
		snprintf(src_file_name, 1001, TEST_FILE_NAME_FORMAT, i * 5 + 5);

		load_graph_from_file_as_list(src_file_name, &graph_list);
		load_graph_from_file(src_file_name, &graph_matrix);

		results[i][0] = run_test_matrix(&graph_matrix);
		results[i][1] = run_test_list(&graph_list);
		sizes[i][0] = calc_matrix_size(&graph_matrix);
		sizes[i][1] = calc_list_size(&graph_list);
	}

	if (print_to_console)
		print_meas_results_tables(results, sizes);
	else
		print_meas_results_tables_to_file(results, sizes);

	free_road_matrix(&graph_matrix);
	free_road_list(&graph_list);
}


long double run_test_matrix(road_graph_t *graph)
{
	road_graph_t res = {.total_cities = 0, .roads_matrix = NULL};
	long long unsigned time_start, time_end;
	long double time_res = 0;

	for (int i = 0; i < TOTAL_TESTS_RUNS; ++i)
	{
		time_start = milliseconds_now();
		(void) floyd_warshall(graph, &res);
		time_end = milliseconds_now();

		time_res += (double)(time_end - time_start) / TOTAL_TESTS_RUNS;
	}

	return time_res;
}


long double run_test_list(road_graph_list_t *graph)
{
	road_graph_list_t res = {.total_cities = 0, .cities = NULL};
	long long unsigned time_start, time_end;
	long double time_res = 0;

	for (int i = 0; i < TOTAL_TESTS_RUNS; ++i)
	{
		time_start = milliseconds_now();
		(void) floyd_warshall_for_list(graph, &res);
		time_end = milliseconds_now();

		time_res += (double)(time_end - time_start) / TOTAL_TESTS_RUNS;
	}

	return time_res;
}
