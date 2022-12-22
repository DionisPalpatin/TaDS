//
// Created by dionis on 02.12.22.
//

#ifndef LAB_02_IO_H
#define LAB_02_IO_H


#include <stdint.h>
#include <stddef.h>

#include <data_types.h>


void greetings(void);
void print_menu(void);
void input_prompt(void);

void print_table(const table_t *table);
void print_entry(const theater_t *theater);
void print_keys(const table_t *table);
void print_table_use_keys(const table_t *table);
void print_header(void);
void print_key_header(void);

void err_message(const char *message);


#endif //LAB_02_IO_H
