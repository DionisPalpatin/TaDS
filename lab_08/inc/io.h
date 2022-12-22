#ifndef IO_H_
#define IO_H_


#include <data_types.h>


void greetings(void);
void print_menu(void);
void input_prompt(void);

void print_road_graph(road_graph_t *roads);
void print_matrix(int **matrix, size_t rows, size_t cols);

void err_message(const char *message);


#endif