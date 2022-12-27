#ifndef IO_H_
#define IO_H_


#include <data_types.h>


void greetings(void);
void print_menu(void);
void input_prompt(void);

void print_road_graph(road_graph_t *roads);
void print_matrix(int **matrix, size_t rows, size_t cols);
void print_list_as_matrix(road_graph_list_t *roads);

void print_meas_results_tables(long double results[10][2], size_t sizes[10][2]);
void print_meas_results_tables_to_file(long double results[10][2], size_t sizes[10][2]);

void err_message(const char *message);

void free_stdin(void);


#endif