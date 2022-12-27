#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <data_types.h>
#include <constants.h>
#include <graph.h>
#include <io.h>


void free_road_matrix(road_graph_t *roads)
{
	if (!roads)
		return;

	for (size_t i = 0; i < roads->total_cities; ++i)
		free(roads->roads_matrix[i]);
	free(roads->roads_matrix);
}


errors_t init_road_matrix(road_graph_t *roads, size_t total_cities)
{
	assert(roads && total_cities > 0);

	errors_t exit_code = OK;

	if (roads->roads_matrix)
		free_road_matrix(roads);

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

	if (src_f && src_f != stdin)
		fclose(src_f);

	return exit_code;
}


void load_graph_manually(road_graph_t *roads)
{
	assert(roads);

	printf("Graph must be inputted in the next format:\n"
		   "1) input quantity of cities (ineger number greater then zero)\n"
		   "2) input graph in format 'first_city_num sec_city_num road_len'.\n\n\n"
		   "Input quantity of cities: ");

	size_t total_roads = 0;
	free_stdin();
	while (scanf("%zu", &total_roads) != 1)
	{
		err_message(STANDARD_ERR_MESS);
		free_stdin();
	}
	free_stdin();

	if (init_road_matrix(roads, total_roads) != OK)
		return;

	printf("When your input will be finished, type 'end'.\nInput graph:\n");
	char *string = NULL;
	size_t len = 0;
	while (getline(&string, &len, stdin) > 0 && strcmp("end\n", string) != 0)
	{
		char *end_ptr = NULL;
		size_t c1, c2;
		int road;

		char *new_str_c = strchr(string, '\n');
		if (new_str_c)
			*new_str_c = '\0';

		len = strlen(string);

		if (len == 0)
		{
			err_message(STANDARD_ERR_MESS);
			free_stdin();
		}
		else
		{
			c1 = strtoul(string, &end_ptr, 10);
			c2 = strtoul(end_ptr, &end_ptr, 10);
			road = (int) strtol(end_ptr, &end_ptr, 10);

			if (*end_ptr != '\0' || road == 0 || road == 10000 || c1 < 1 || c1 > total_roads || c2 < 1 || c2 > total_roads || c1 == c2)
			{
				err_message(STANDARD_ERR_MESS);
				free_stdin();
			}
			else
				roads->roads_matrix[c1 - 1][c2 - 1] = road;
		}
	}

	free_stdin();
}


errors_t read_road_matrix(FILE *src, road_graph_t *roads)
{
	assert(src && roads);

	errors_t exit_code = OK;

	for (size_t i = 0; i < roads->total_cities && exit_code == OK; ++i)
	{
		for (size_t j = 0; j < roads->total_cities && exit_code == OK; ++j)
		{
			if (fscanf(src, "%d", &roads->roads_matrix[i][j]) != 1)
			{
				err_message(STANDARD_ERR_MESS);
				exit_code = READ_ERR;
			}
		}
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




void free_road_list(road_graph_list_t *roads)
{
	if (roads == NULL)
		return;

	for (size_t i = 0; i < roads->total_cities; ++i)
		free_conn_cities(roads->cities + i);
	free(roads->cities);
}


void free_conn_cities(beg_city_t *city)
{
	if (!city)
		return;

	conn_city_t *cur = city->next;
	while (cur)
	{
		conn_city_t *temp = cur->next;
		free(cur);
		cur = temp;
	}
}


errors_t load_graph_from_file_as_list(const char *file_name, road_graph_list_t *roads)
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
		exit_code = init_roads_matrix_list(roads, total_cities);
	if (exit_code == OK)
		exit_code = read_roads(src_f, roads);

	if (src_f)
		fclose(src_f);

	return exit_code;
}


errors_t init_roads_matrix_list(road_graph_list_t *roads, size_t total_cities)
{
	assert(roads && total_cities > 0);

	errors_t exit_code = OK;

	roads->cities = calloc(total_cities, sizeof(beg_city_t));
	if (!roads->cities)
	{
		err_message(MEM_ALLOC_ERR_MESS);
		exit_code = MEM_ALLOC_ERR;
	}

	if (exit_code == OK)
		roads->total_cities = total_cities;

	return exit_code;
}


errors_t read_roads(FILE *src, road_graph_list_t *roads)
{
	assert(src && roads);

	errors_t exit_code = OK;

	for (size_t i = 0; i < roads->total_cities && exit_code == OK; ++i)
		for (size_t j = 0; j < roads->total_cities && exit_code == OK; ++j)
		{
			int new_road = 0;

			if (fscanf(src, "%d", &new_road) != 1)
			{
				err_message(STANDARD_ERR_MESS);
				exit_code = READ_ERR;
			}
			else if (new_road > 0 && new_road < INF)
				exit_code = insert_new_city(roads->cities + i, new_road, j);
		}

	return exit_code;
}


errors_t insert_new_city(beg_city_t *to_which_conn, int dist, size_t ind)
{
	assert(to_which_conn);

	errors_t exit_code = OK;

	conn_city_t *new_city = NULL;
	exit_code = creat_new_city(&new_city, dist, ind);
	if (exit_code == OK)
	{
		if (to_which_conn->next == NULL)
			to_which_conn->next = new_city;
		else
		{
			conn_city_t *cur = to_which_conn->next;
			while (cur->next != NULL)
				cur = cur->next;
			cur->next = new_city;
		}
	}

	return exit_code;
}


errors_t creat_new_city(conn_city_t **new_city, int dist, size_t ind)
{
	assert(new_city);

	errors_t exit_code = OK;

	*new_city = calloc(1, sizeof(conn_city_t));
	if (!*new_city)
	{
		err_message(MEM_ALLOC_ERR_MESS);
		exit_code = MEM_ALLOC_ERR;
	}
	else
	{
		(*new_city)->next = NULL;
		(*new_city)->dist = dist;
		(*new_city)->ind = ind;
	}

	return exit_code;
}


errors_t floyd_warshall_for_list(road_graph_list_t *roads, road_graph_list_t *results)
{
	assert(roads && results);

	errors_t exit_code = init_roads_matrix_list(results, roads->total_cities);
	if (!exit_code)
	{
		int roads_matrix[roads->total_cities][roads->total_cities];

		for (size_t i = 0; i < roads->total_cities; ++i)
			for (size_t j = 0; j < roads->total_cities; ++j)
				roads_matrix[i][j] = INF;
		for (size_t i = 0; i < roads->total_cities; ++i)
		{
			roads_matrix[i][i] = 0;

			conn_city_t *cur = roads->cities[i].next;
			while (cur)
			{
				roads_matrix[i][cur->ind] = cur->dist;
				cur = cur->next;
			}
		}

		for (size_t k = 0; k < results->total_cities; k++)
			for (size_t i = 0; i < results->total_cities; i++)
				for (size_t j = 0; j < results->total_cities; j++)
					if (roads_matrix[i][k] + roads_matrix[k][j] < roads_matrix[i][j] && roads_matrix[i][k] < INF && roads_matrix[k][j] < INF)
						roads_matrix[i][j] = roads_matrix[i][k] + roads_matrix[k][j];

		for (size_t i = 0; i < results->total_cities && exit_code == OK; ++i)
			for (size_t j = 0; j < results->total_cities && exit_code == OK; ++j)
				if (roads_matrix[i][j] < INF && roads_matrix[i][j] > 0)
					exit_code = insert_new_city(results->cities + i, roads_matrix[i][j], j);
	}

	return exit_code;
}


size_t calc_matrix_size(road_graph_t *graph)
{
	return sizeof(size_t) + sizeof(int *) * graph->total_cities + sizeof(int) * graph->total_cities * graph->total_cities;
}


size_t calc_list_size(road_graph_list_t *graph)
{
	size_t size = sizeof(size_t) + sizeof(beg_city_t *) * graph->total_cities;

	for (size_t i = 0; i < graph->total_cities; ++i)
	{
		conn_city_t *cur = graph->cities[i].next;
		while (cur)
		{
			size += sizeof(conn_city_t);
			cur = cur->next;
		}
	}

	return size;
}
