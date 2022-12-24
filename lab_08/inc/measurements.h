//
// Created by dionis on 13.12.22.
//

#ifndef LAB_03_MEASUREMENTS_H
#define LAB_03_MEASUREMENTS_H


#include <data_types.h>
#include <graph.h>


unsigned long long milliseconds_now(void);
void compare_realizations(int print_to_console);
long double run_test_matrix(road_graph_t *graph);
long double run_test_list(road_graph_list_t *graph);


#endif //LAB_03_MEASUREMENTS_H
