#include <stdio.h>

#include <tests.h>


int main(void)
{
    int failed_tests = 0;

    failed_tests += run_all_tests_array();
    failed_tests += run_all_tests_file();
    failed_tests += run_all_tests_sort();

    printf("Total failed tests: %d\n", failed_tests);

    return failed_tests;
}
