#include <stdio.h>
#include <stdbool.h>

#include <errors.h>
#include <constants.h>
#include <structs.h>


int main(void)
{
    int exit_code = OK;
    nums_storage_t nums_storage;
    prog_state_t prog_state = {.no_nums_changes = false, .repeat_input = true};

    printf(GREETING);

    return exit_code;
}