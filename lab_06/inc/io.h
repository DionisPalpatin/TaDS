#ifndef _IO_H_
#define _IO_H_

#include <data_types.h>


void greetings(void);
void print_menu(void);
void input_prompt(void);

void print_tree(tree_t *tree);

void print_meas_results_tables(long double results[8][9], double *pers);
void print_meas_results_tables_to_file(long double results[8][9]);

void err_message(const char *message);


#endif // _IO_H_