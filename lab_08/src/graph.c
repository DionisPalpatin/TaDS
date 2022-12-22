#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <data_types.h>
#include <constants.h>
#include <graph.h>
#include <io.h>


void free_road_matrix(road_graph_t *roads)
{
	assert(roads);

	for (size_t i = 0; i < roads->total_cities; ++i)
		free(roads->roads_matrix[i]);
	free(roads->roads_matrix);
}


errors_t init_road_matrix(road_graph_t *roads, size_t total_cities)
{
	assert(roads && total_cities > 0);

	errors_t exit_code = OK;

	roads->roads_matrix = calloc(total_cities, sizeof(int *));
	if (!roads->roads_matrix)
	{
		err_message(MEM_ALLOC_ERR_MESS);
		exit_code = MEM_ALLOC_ERR;
	}
	else
	{
		for (size_t i = 0; i < total_cities && exit_code == OK; ++i)
		{
			roads->roads_matrix[i] = malloc(total_cities * sizeof(int));
			if (!roads->roads_matrix[i])
			{
				err_message(MEM_ALLOC_ERR_MESS);
				exit_code = MEM_ALLOC_ERR;
				free_road_matrix(roads);
			}
			else
				for (size_t j = 0; j < total_cities; ++j)
					roads->roads_matrix[i][j] = INF;
		}
	}

	if (exit_code == OK)
		roads->total_cities = total_cities;

	return exit_code;
}


errors_t load_graph_from_file(const char *file_name, road_graph_t *roads)
{
	assert(file_name && roads);

	errors_t exit_code = OK;

	FILE *src_f = fopen(file_name, "r");
	if (!src_f)
	{
		err_message(FILE_ERR_MESS);
		exit_code = FILE_ERR;
	}

	size_t total_cities = 0;
	if (exit_code == OK && (fscanf(src_f, "%zu", &total_cities) != 1 || total_cities == 0))
	{
		err_message(STANDARD_ERR_MESS);
		exit_code = READ_ERR;
	}

	if (exit_code == OK)
		exit_code = init_road_matrix(roads, total_cities);
	if (exit_code == OK)
		exit_code = read_road_matrix(src_f, roads);

	if (src_f)
		fclose(src_f);

	return exit_code;
}


errors_t read_road_matrix(FILE *src, road_graph_t *roads)
{
	assert(src && roads);

	errors_t exit_code = OK;

	for (size_t i = 0; i < roads->total_cities && exit_code == OK; ++i)
		for (size_t j = 0; j < roads->total_cities && exit_code == OK; ++j)
			if (fscanf(src, "%d", &roads->roads_matrix[i][j]) != 1)
			{
				err_message(STANDARD_ERR_MESS);
				exit_code = READ_ERR;
			}

	return exit_code;
}


errors_t floyd_warshall(road_graph_t *roads, road_graph_t *results)
{
	assert(roads && results);

	errors_t exit_code = init_road_matrix(results, roads->total_cities);
	if (!exit_code)
	{
		for (size_t i = 0; i < roads->total_cities; ++i)
			for (size_t j = 0; j < roads->total_cities; ++j)
				results->roads_matrix[i][j] = roads->roads_matrix[i][j];

		for (size_t k = 0; k < results->total_cities; k++)
			for (size_t i = 0; i < results->total_cities; i++)
				for (size_t j = 0; j < results->total_cities; j++)
					if (results->roads_matrix[i][k] + results->roads_matrix[k][j] < results->roads_matrix[i][j])
						results->roads_matrix[i][j] = results->roads_matrix[i][k] + results->roads_matrix[k][j];
	}

	return exit_code;
}
