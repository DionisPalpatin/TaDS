#ifndef LAB_02_LOAD_DATA_H
#define LAB_02_LOAD_DATA_H


#include <stdio.h>

#include <data_types.h>


error_t open_file(FILE **file, const char *file_name, const char *mode);
error_t load_data_from_file(table_t *table, const char *file_name);
error_t read_theater_info_from_stdin(theater_t *theater);
error_t read_theater_info(FILE *file, theater_t *theater);
error_t save_table_to_file(table_t *table, const char *file_name);

int end_of_input(theater_t *theater);


#endif
