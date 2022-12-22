#include <check.h>

#include <file.h>
#include <tests.h>



/* ----- Проверка функции check_arguments ----- */




START_TEST(test_process_parameters_null_argv)
{
    int exit_code = check_arguments(0, NULL);

    ck_assert_int_eq(NULL_PTR, exit_code);
}
END_TEST


START_TEST(test_process_parameters_incorrect_argc)
{
    char *argv[] = {"./app.exe", "file_src", "file_out"};
    int exit_code = check_arguments(0, argv);

    ck_assert_int_eq(INCORRECT_ARGS_QUAN, exit_code);
}
END_TEST


START_TEST(test_process_parameters_incorrect_last_arg)
{
    char *argv[] = {"./app.exe", "file_src", "file_out", "fk"};
    int exit_code = check_arguments(4, argv);

    ck_assert_int_eq(INCORRECT_ARGUMENT, exit_code);
}
END_TEST


START_TEST(test_process_parameters_correct_three_args)
{
    char *argv[] = {"./app.exe", "file_src", "file_out"};
    int exit_code = check_arguments(3, argv);

    ck_assert_int_eq(OK, exit_code);
}
END_TEST


START_TEST(test_process_parameters_correct_four_args)
{
    char *argv[] = {"./app.exe", "file_src", "file_out", "f"};
    int exit_code = check_arguments(4, argv);

    ck_assert_int_eq(OK, exit_code);
}
END_TEST


Suite* process_parameters_suite(void)
{
    Suite *new_suite;
    TCase *negatives, *positives;

    new_suite = suite_create("check_arguments");
    negatives = tcase_create("negatives");
    positives = tcase_create("positives");

    tcase_add_test(negatives, test_process_parameters_null_argv);
    tcase_add_test(negatives, test_process_parameters_incorrect_argc);
    tcase_add_test(negatives, test_process_parameters_incorrect_last_arg);

    tcase_add_test(positives, test_process_parameters_correct_three_args);
    tcase_add_test(positives, test_process_parameters_correct_four_args);

    suite_add_tcase(new_suite, negatives);
    suite_add_tcase(new_suite, positives);

    return new_suite;
}




/* ----- Функция, запускающая все тесты ----- */




int run_all_tests_file(void)
{
    int failed_tests = 0;
    Suite *testing_suite;
    SRunner *runner;

    testing_suite = process_parameters_suite();
    runner = srunner_create(testing_suite);
    srunner_run_all(runner, CK_VERBOSE);
    failed_tests += srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed_tests;
}
