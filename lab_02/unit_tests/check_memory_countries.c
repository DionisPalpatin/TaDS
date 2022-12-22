#include <check_main.h>
#include "memory_countries.h"

//neg
START_TEST(er_size)
{
    int rc = 0;
    country_t *array = NULL;

    array = allocate_struct_country(-1);
    if (array == NULL)
        rc = -1;

    ck_assert_int_eq(rc, -1);
}
END_TEST

START_TEST(null_size)
{
    country_t *array = NULL;
    int size = 0, rc = 0;

    array = allocate_struct_country(size);
    if (array == NULL)
        rc = -1;

    ck_assert_int_eq(rc, -1);

    free_struct_country(&array, &size);
    free_struct_country(&array, &size);
}
END_TEST

START_TEST(str_er_size)
{
    char *str = NULL;
    int rc = 0;

    str = allocate_name_str(-10);
    if (str == NULL)
        rc = -1;

    ck_assert_int_eq(rc, -1);

    free_name_str(&str);
}

START_TEST(str_null_size)
{
    char *str = NULL;
    int rc = 0;

    str = allocate_name_str(0);
    if (str == NULL)
        rc = -1;

    ck_assert_int_eq(rc, -1);

    free_name_str(&str);
}

//pos
START_TEST(ok_size)
{
    int rc = 0, size = 100;
    country_t *array = NULL;

    array = (country_t *) allocate_struct_country(size);
    if (array == NULL)
        rc = -1;

    ck_assert_int_eq(rc, 0);

    free_struct_country(&array, &size);
}
END_TEST

START_TEST(str_ok_size)
{
    int rc = 0;
    char *str = NULL;

    str = allocate_name_str(100);
    if (str == NULL)
        rc = -1;

    ck_assert_int_eq(rc, 0);

    free_name_str(&str);
}
END_TEST


Suite *memory_countries_suite(void)
{
    Suite *s = suite_create("memory_country");

    TCase *tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, er_size);
    tcase_add_test(tc_neg, null_size);
    tcase_add_test(tc_neg, str_er_size);
    tcase_add_test(tc_neg, str_null_size);

    suite_add_tcase(s, tc_neg);

    TCase *tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, ok_size);
    tcase_add_test(tc_pos, str_ok_size);

    suite_add_tcase(s, tc_pos);

    return s;
}