#ifndef GRAPH_H_
#define GRAPH_H_


#include <data_types.h>


void free_road_matrix(road_graph_t *roads);

errors_t init_road_matrix(road_graph_t *roads, size_t total_cities);
errors_t load_graph_from_file(const char *file_name, road_graph_t *roads);
void load_graph_manually(road_graph_t *roads);
errors_t read_road_matrix(FILE *src, road_graph_t *roads);
errors_t floyd_warshall(road_graph_t *roads, road_graph_t *results);


void free_road_list(road_graph_list_t *roads);
void free_conn_cities(beg_city_t *city);

errors_t load_graph_from_file_as_list(const char *file_name, road_graph_list_t *roads);
errors_t init_roads_matrix_list(road_graph_list_t *roads, size_t total_cities);
errors_t read_roads(FILE *src, road_graph_list_t *roads);
errors_t insert_new_city(beg_city_t *to_which_conn, int dist, size_t ind);
errors_t creat_new_city(conn_city_t **new_city, int dist, size_t ind);
errors_t floyd_warshall_for_list(road_graph_list_t *roads, road_graph_list_t *results);

size_t calc_matrix_size(road_graph_t *graph);
size_t calc_list_size(road_graph_list_t *graph);


#endif