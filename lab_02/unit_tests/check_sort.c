#include <stdlib.h>
#include <check.h>

#include "sort.h"
#include <tests.h>




/* ----- Проверка функции sort ----- */




START_TEST(test_sort_null_first_ptr)
{
    int *array_beg = NULL, exit_code = OK;

    exit_code = mysort(array_beg, 10, sizeof(int), comparator);

    ck_assert_int_eq(exit_code, NULL_PTR);
}
END_TEST


START_TEST(test_sort_null_last_ptr)
{
    int temp = 0, exit_code = OK;
    int *array_beg = &temp;

    exit_code = mysort(array_beg, 10, sizeof(int), NULL);

    ck_assert_int_eq(exit_code, NULL_PTR);
}
END_TEST


START_TEST(test_sort_correct_array_many_elems)
{
    int exit_code = OK;
    int array[] = {5, 3, 2, -1, 0};
    int res_array[] = {-1, 0, 2, 3, 5};

    exit_code = mysort(array, 5, sizeof(int), comparator);

    ck_assert_int_eq(exit_code, OK);
    ck_assert_int_eq(OK, memcmp(array, res_array, 5 * sizeof(int)));
}
END_TEST


START_TEST(test_sort_correct_array_one_elem)
{
    int exit_code = OK;
    int array[] = {0};
    int res_array[] = {0};

    exit_code = mysort(array, 1, sizeof(int), comparator);

    ck_assert_int_eq(exit_code, OK);
    ck_assert_int_eq(OK, memcmp(array, res_array, sizeof(int)));
}
END_TEST


START_TEST(test_sort_test_double_comp)
{
    int exit_code = OK;
    double array[] = {1.593, -0.719, 10.431, 11.317, 0.044, -120.295, 0.052, -30.576};
    double sorted_array[] = {-120.295, -30.576, -0.719, 0.044, 0.052, 1.593, 10.431, 11.317};
    size_t len = 8;

    exit_code = mysort(array, len, sizeof(double), comparator_double);

    ck_assert_int_eq(OK, exit_code);
    ck_assert_int_eq(OK, memcmp(array, sorted_array, len * sizeof(double)));
}
END_TEST


Suite* sort_suite(void)
{
    Suite *new_suite;
    TCase *negatives, *positives;

    new_suite = suite_create("sort");
    negatives = tcase_create("negatives");
    positives = tcase_create("positives");

    tcase_add_test(negatives, test_sort_null_first_ptr);
    tcase_add_test(negatives, test_sort_null_last_ptr);

    tcase_add_test(positives, test_sort_correct_array_many_elems);
    tcase_add_test(positives, test_sort_correct_array_one_elem);
    tcase_add_test(positives, test_sort_test_double_comp);

    suite_add_tcase(new_suite, negatives);
    suite_add_tcase(new_suite, positives);

    return new_suite;
}




/* ----- Проверка функции swap  ----- */




START_TEST(test_swap_int)
{
    int first_num = 1, sec_num = 2, first_num_mem = 1, sec_num_mem = 2;

    swap(&first_num, &sec_num, sizeof(int));
    ck_assert_int_eq(SUCCESS, first_num == sec_num_mem && sec_num == first_num_mem);
}
END_TEST


START_TEST(test_swap_char)
{
    char first_sym = '*', sec_sym = ':', first_sym_mem = '*', sec_sym_mem = ':';

    swap(&first_sym, &sec_sym, sizeof(char));
    ck_assert_int_eq(SUCCESS, first_sym == sec_sym_mem && sec_sym == first_sym_mem);
}
END_TEST


Suite* swap_suite(void)
{
    Suite *new_suite;
    TCase *positives;

    new_suite = suite_create("swap");
    positives = tcase_create("positives");

    tcase_add_test(positives, test_swap_int);
    tcase_add_test(positives, test_swap_char);

    suite_add_tcase(new_suite, positives);

    return new_suite;
}




/* ----- Проверка функции key  ----- */




START_TEST(test_key_null_first_ptr)
{
    int *temp2 = NULL, *temp3 = NULL, *temp4 = NULL;
    int exit_code = OK;

    exit_code = key(NULL, temp2, &temp3, &temp4);

    ck_assert_int_eq(exit_code, NULL_PTR);
}
END_TEST


START_TEST(test_key_null_sec_ptr)
{
    int *temp1= NULL, *temp3 = NULL, *temp4 = NULL;
    int exit_code = OK;

    exit_code = key(temp1, NULL, &temp3, &temp4);

    ck_assert_int_eq(exit_code, NULL_PTR);
}
END_TEST


START_TEST(test_key_null_third_ptr)
{
    int *temp1 = NULL, *temp2 = NULL, *temp4 = NULL;
    int exit_code = OK;

    exit_code = key(temp1, temp2, NULL, &temp4);

    ck_assert_int_eq(exit_code, NULL_PTR);
}
END_TEST


START_TEST(test_key_null_fourth_ptr)
{
    int *temp1 = NULL, *temp2 = NULL, *temp3 = NULL;
    int exit_code = OK;

    exit_code = key(temp1, temp2, &temp3, NULL);

    ck_assert_int_eq(exit_code, NULL_PTR);
}
END_TEST


START_TEST(test_key_last_neg_elem_is_first_elem_in_src_array)
{
    int exit_code = OK;
    int array[] = {-1, 2};
    int *new_arr_beg = NULL, *new_arr_end = NULL;

    exit_code = key(array, array + 2, &new_arr_beg, &new_arr_end);

    ck_assert_int_eq(exit_code, EMPTY_NEW_ARRAY);
}
END_TEST


START_TEST(test_key_one_elem_in_new_arr)
{
    int exit_code = OK;
    int array[] = {2, -1, 3};
    int *new_array_beg = NULL, *new_array_end = NULL;

    exit_code = key(array, array + 3, &new_array_beg, &new_array_end);

    ck_assert_int_eq(OK, exit_code);
    ck_assert_int_eq(SUCCESS, new_array_beg != NULL && new_array_end != NULL);
    ck_assert_int_eq(OK, memcmp(array, new_array_beg, sizeof(int)));

    free(new_array_beg);
}
END_TEST


START_TEST(test_key_many_elems_in_new_arr)
{
    int exit_code = OK;
    int array[] = {2, 1, 3, 4, -1, 6};
    int *new_array_beg = NULL, *new_array_end = NULL;

    exit_code = key(array, array + 6, &new_array_beg, &new_array_end);

    ck_assert_int_eq(OK, exit_code);
    ck_assert_int_eq(SUCCESS, new_array_beg != NULL && new_array_end != NULL);
    ck_assert_int_eq(OK, memcmp(array, new_array_beg, 4 * sizeof(int)));

    free(new_array_beg);
}
END_TEST


START_TEST(test_key_some_neg_elems_in_src_array)
{
    int exit_code = OK;
    int array[] = {2, -11, 3, 88, 99,-4, -1, 6};
    int *new_array_beg = NULL, *new_array_end = NULL;

    exit_code = key(array, array + 8, &new_array_beg, &new_array_end);

    ck_assert_int_eq(OK, exit_code);
    ck_assert_int_eq(SUCCESS, new_array_beg != NULL && new_array_end != NULL);
    ck_assert_int_eq(OK, memcmp(array, new_array_beg, 6 * sizeof(int)));

    free(new_array_beg);
}
END_TEST


Suite* key_suite(void)
{
    Suite *new_suite;
    TCase *negatives, *positives;

    new_suite = suite_create("key");
    negatives = tcase_create("negatives");
    positives = tcase_create("positives");

    tcase_add_test(negatives, test_key_null_first_ptr);
    tcase_add_test(negatives, test_key_null_sec_ptr);
    tcase_add_test(negatives, test_key_null_third_ptr);
    tcase_add_test(negatives, test_key_null_fourth_ptr);
    tcase_add_test(negatives, test_key_last_neg_elem_is_first_elem_in_src_array);

    tcase_add_test(positives, test_key_one_elem_in_new_arr);
    tcase_add_test(positives, test_key_many_elems_in_new_arr);
    tcase_add_test(positives, test_key_some_neg_elems_in_src_array);

    suite_add_tcase(new_suite, negatives);
    suite_add_tcase(new_suite, positives);

    return new_suite;
}




/* ----- Проверка функции array_processing  ----- */




START_TEST(test_array_processing_null_first_ptr)
{
    int *temp2 = NULL, *temp3 = NULL, *temp4 = NULL;
    int exit_code = OK;

    exit_code = array_processing(NULL, temp2, &temp3, &temp4, NULL);

    ck_assert_int_eq(exit_code, NULL_PTR);
}
END_TEST


START_TEST(test_array_processing_null_sec_ptr)
{
    int *temp1 = NULL, *temp3 = NULL, *temp4 = NULL;
    int exit_code = OK;

    exit_code = array_processing(temp1, NULL, &temp3, &temp4, NULL);

    ck_assert_int_eq(exit_code, NULL_PTR);
}
END_TEST


START_TEST(test_array_processing_null_third_ptr)
{
    int *temp1 = NULL, *temp2 = NULL, *temp4 = NULL;
    int exit_code = OK;

    exit_code = array_processing(temp1, temp2, NULL, &temp4, NULL);

    ck_assert_int_eq(exit_code, NULL_PTR);
}
END_TEST


START_TEST(test_array_processing_null_fourth_ptr)
{
    int *temp1 = NULL, *temp2 = NULL, *temp3 = NULL;
    int exit_code = OK;

    exit_code = array_processing(temp1, temp2, &temp3, NULL, NULL);

    ck_assert_int_eq(exit_code, NULL_PTR);
}
END_TEST


START_TEST(test_array_processing_sort_src_array)
{
    int exit_code = OK;
    int array[] = {2, 1, 3, 4, -1, 6};
    int *array_beg = array, *array_end = array + 6;
    int sorted_array[] = {-1, 1, 2, 3, 4, 6};

    exit_code = array_processing(array_beg, array_end, &array_beg, &array_end, NULL);

    ck_assert_int_eq(OK, exit_code);
    ck_assert_int_eq(OK, memcmp(array, sorted_array, 6 * sizeof(int)));
}


START_TEST(test_array_processing_sort_new_array)
{
    int exit_code = OK;
    int array[] = {2, 1, 3, 4, -1, 6};
    int *array_beg = NULL, *array_end = NULL;
    int sorted_array[] = {1, 2,3, 4};

    exit_code = array_processing(array, array + 6, &array_beg, &array_end, key);

    ck_assert_int_eq(OK, exit_code);
    ck_assert_int_eq(SUCCESS, array_beg != NULL && array_end != NULL);
    ck_assert_int_eq(OK, memcmp(array_beg, sorted_array, array_end - array_beg));

    free(array_beg);
}


Suite* array_processing_suite(void)
{
    Suite *new_suite;
    TCase *negatives, *positives;

    new_suite = suite_create("array_processing");
    negatives = tcase_create("negatives");
    positives = tcase_create("positives");

    tcase_add_test(negatives, test_array_processing_null_first_ptr);
    tcase_add_test(negatives, test_array_processing_null_sec_ptr);
    tcase_add_test(negatives, test_array_processing_null_third_ptr);
    tcase_add_test(negatives, test_array_processing_null_fourth_ptr);

    tcase_add_test(positives, test_array_processing_sort_src_array);
    tcase_add_test(positives, test_array_processing_sort_new_array);

    suite_add_tcase(new_suite, negatives);
    suite_add_tcase(new_suite, positives);

    return new_suite;
}




/* ----- Функция, запускающая все тесты ----- */




int run_all_tests_sort(void)
{
    int failed_tests = 0;
    Suite *testing_suite;
    SRunner *runner;

    testing_suite = array_processing_suite();
    runner = srunner_create(testing_suite);
    srunner_run_all(runner, CK_VERBOSE);
    failed_tests += srunner_ntests_failed(runner);
    srunner_free(runner);

    testing_suite = sort_suite();
    runner = srunner_create(testing_suite);
    srunner_run_all(runner, CK_VERBOSE);
    failed_tests += srunner_ntests_failed(runner);
    srunner_free(runner);

    testing_suite = key_suite();
    runner = srunner_create(testing_suite);
    srunner_run_all(runner, CK_VERBOSE);
    failed_tests += srunner_ntests_failed(runner);
    srunner_free(runner);

    testing_suite = swap_suite();
    runner = srunner_create(testing_suite);
    srunner_run_all(runner, CK_VERBOSE);
    failed_tests += srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed_tests;
}
