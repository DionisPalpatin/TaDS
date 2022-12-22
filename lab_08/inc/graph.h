#ifndef GRAPH_H_
#define GRAPH_H_


#include <data_types.h>


void free_road_matrix(road_graph_t *roads);

errors_t init_road_matrix(road_graph_t *roads, size_t total_cities);
errors_t load_graph_from_file(const char *file_name, road_graph_t *roads);
errors_t read_road_matrix(FILE *src, road_graph_t *roads);
errors_t floyd_warshall(road_graph_t *roads, road_graph_t *results);


#endif