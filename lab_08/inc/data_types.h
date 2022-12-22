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


typedef struct road_graph
{
	size_t total_cities;
	int **roads_matrix;
} road_graph_t;


#endif //LAB_08_DATA_TYPES_H
