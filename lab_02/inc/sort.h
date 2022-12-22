//
// Created by dionis on 02.12.22.
//

#ifndef LAB_02_SORT_H
#define LAB_02_SORT_H


#include <stdint.h>

#include <data_types.h>


void sort_table_bubble(table_t *table);
void sort_table_quick_sort(table_t *table);
void sort_key_table_bubble(table_t *table);
void sort_key_table_quick_sort(table_t *table);

void sort_keys(table_t *table);
void sort_table(table_t *table);

void swap(void *first, void *sec, size_t size);
int compare_table_els(const void *ptr1, const void *ptr2);
int compare_key_els(const void *ptr1, const void *ptr2);


#endif //LAB_02_SORT_H
