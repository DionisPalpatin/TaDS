#ifndef IO_H
#define IO_H


#include <constants.h>
#include <data_types.h>


void greetings(void);
void print_menu(void);
void input_prompt(void);

void print_coord_format(const matrix_std_t *matrix);
void print_std_format(const matrix_std_t *matrix);
void print_sparse_format(const matrix_sparse_t *matrix);

void print_meas_results_tables(long double results[8][9], double *pers);
void print_meas_results_tables_to_file(long double results[8][9]);

void err_message(const char *message);


#endif // IO_H
