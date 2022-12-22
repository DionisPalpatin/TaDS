//
// Created by dionis on 02.12.22.
//

#ifndef LAB_02_MEASUREMENTS_H
#define LAB_02_MEASUREMENTS_H


#include <stdint.h>

#include <data_types.h>


unsigned long long milliseconds_now(void);
void compare_sorts(table_t *table);
long double run_test(const table_t *table, size_t iters, void (*sort_func)(table_t *));


#endif //LAB_02_MEASUREMENTS_H
