#ifndef LAB_01_INPUT_OUTPUT_H
#define LAB_01_INPUT_OUTPUT_H

#include <stddef.h>
#include <stdbool.h>

#include <constants.h>
#include <errors.h>
#include <structs.h>


void write_num_to_struct(const char *num_str, num_t *num);

int get_num(num_t *num, prog_state_t *prog_state);

bool validate_num(num_t *number);

#endif
