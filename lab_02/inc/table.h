//
// Created by dionis on 02.12.22.
//

#ifndef LAB_02_TABLE_H
#define LAB_02_TABLE_H


#include <data_types.h>


void creat_key_table(table_t *table);
void find_entries(const table_t *table);
void clean_table(table_t *table);

error_t delete_entry(table_t *table);
error_t add_entry(table_t *table);

size_t get_entry_id(const table_t *table, const char *name);


#endif //LAB_02_TABLE_H
