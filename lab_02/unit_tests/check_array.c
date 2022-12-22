#include <stdlib.h>
#include <check.h>

#include <array.h>




/* ----- Проверка функции array_alloc ----- */



START_TEST(test_array_alloc_null_first_ptr)
{
    int exit_code = OK;
    int *temp_ptr_2 = NULL;

    exit_code = array_alloc(NULL, &temp_ptr_2, 5);

    ck_assert_int_eq(NULL_PTR, exit_code);
}


START_TEST(test_array_alloc_null_sec_ptr)
{
    int exit_code = OK;
    int *temp_ptr_1 = NULL;

    exit_code = array_alloc(&temp_ptr_1, NULL, 5);

    ck_assert_int_eq(NULL_PTR, exit_code);
}


START_TEST(test_array_alloc_correct_params)
{
    int exit_code = OK;
    int *temp_ptr_1 = NULL, *temp_ptr_2 = NULL;

    exit_code = array_alloc(&temp_ptr_1, &temp_ptr_2, 5);
    free(temp_ptr_1);

    ck_assert_int_eq(OK, exit_code);
}


Suite* test_array_alloc(void)
{
    Suite *new_suite;
    TCase *negatives, *positives;

    new_suite = suite_create("array_alloc");
    negatives = tcase_create("negatives");
    positives = tcase_create("positives");

    tcase_add_test(negatives, test_array_alloc_null_first_ptr);
    tcase_add_test(negatives, test_array_alloc_null_sec_ptr);

    tcase_add_test(positives, test_array_alloc_correct_params);

    suite_add_tcase(new_suite, negatives);
    suite_add_tcase(new_suite, positives);

    return new_suite;
}




/* ----- Функция, запускающая все тесты ----- */




int run_all_tests_array(void)
{
    int failed_tests = 0;
    Suite *testing_suite;
    SRunner *runner;

    testing_suite = test_array_alloc();
    runner = srunner_create(testing_suite);
    srunner_run_all(runner, CK_VERBOSE);
    failed_tests += srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed_tests;
}
