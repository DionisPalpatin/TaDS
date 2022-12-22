#include "checks.h"
#include <check_main.h>
#define UNIT_TESTS_FILE "unit_test.txt"

//neg
START_TEST(none_file)
{
    FILE *f = NULL;
    int rc = check_file(f);

    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(empty_file)
{
    FILE *f = NULL;
    f = fopen(UNIT_TESTS_FILE, "w+");

    int rc = check_file(f);

    ck_assert_int_eq(rc, 2);

    remove(UNIT_TESTS_FILE); //
}
END_TEST

START_TEST(args_er_1)
{
    int rc = check_argc(-10, "a");
    ck_assert_int_eq(rc, 6);
}
END_TEST

START_TEST(args_er_2)
{
    int rc = check_argc(0, "pg");
    ck_assert_int_eq(rc, 6);
}
END_TEST

START_TEST(args_er_3)
{
    int rc = check_argc(10, "pf");
    ck_assert_int_eq(rc, 6);
}
END_TEST


//pos
START_TEST(file_ok)
{
    FILE *f = NULL;
    f = fopen(UNIT_TESTS_FILE, "w+");

    rewind(f);
    fprintf((f), "data\n");
    rewind(f);

    int rc = check_file(f);
    if (rc != 0)
        rc = -1;

    ck_assert_int_eq(rc, 0);

    fclose(f);
    remove(UNIT_TESTS_FILE); //
}
END_TEST

START_TEST(arg_pf)
{
    int rc = check_argc(4, "pf");
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(arg_pb)
{
    int rc = check_argc(4, "pb");
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(arg_s)
{
    int rc = check_argc(4, "s");
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(arg_a)
{
    int rc = check_argc(5, "a");
    ck_assert_int_eq(rc, 0);
}
END_TEST


Suite *checks_suite(void)
{
    Suite *s = suite_create("checks");

    TCase *tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, none_file);
    tcase_add_test(tc_neg, empty_file);
    tcase_add_test(tc_neg, args_er_1);
    tcase_add_test(tc_neg, args_er_2);
    tcase_add_test(tc_neg, args_er_3);

    suite_add_tcase(s, tc_neg);

    TCase *tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, file_ok);
    tcase_add_test(tc_pos, arg_pf);
    tcase_add_test(tc_pos, arg_pb);
    tcase_add_test(tc_pos, arg_a);
    tcase_add_test(tc_pos, arg_s);

    suite_add_tcase(s, tc_pos);

    return s;
}

