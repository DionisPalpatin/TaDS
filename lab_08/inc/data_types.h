#ifndef LAB_08_DATA_TYPES_H
#define LAB_08_DATA_TYPES_H


#include <stddef.h>


typedef enum errors
{
	OK = 0,
	FILE_ERR = 1,
	READ_ERR = 2,
	MEM_ALLOC_ERR = 3,
	CHOICE_ERR = 4,
	COMM_ERR = 5,
	WAY_ERR = 6
} errors_t;


// Просто матрица
typedef struct road_graph
{
	size_t total_cities;
	int **roads_matrix;
} road_graph_t;


typedef struct conn_city
{
	size_t ind;
	int dist;
	struct conn_city *next;
} conn_city_t;


typedef struct beg_city
{
	conn_city_t *next;
} beg_city_t;


// Граф в виде списка
typedef struct road_graph_list
{
	size_t total_cities;
	beg_city_t *cities;
} road_graph_list_t;


#endif //LAB_08_DATA_TYPES_H
