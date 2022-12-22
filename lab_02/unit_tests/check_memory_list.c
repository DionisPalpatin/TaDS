#include <check_main.h>
#include "memory_list.h"

//pos
START_TEST(list_push_ok)
{
    int rc = 0;
    node_t *head = NULL;

    int array[5] = {1, 2, 3 ,4, 5};

    rc = list_push(&head, array);
    if (rc != 0 || head == NULL || *(int *)head->data != *(array))
        rc = -1;

    ck_assert_int_eq(rc, 0);

    free_list(&head);
}
END_TEST

START_TEST(node_create_ok)
{
    int rc = 0;
    node_t *head = NULL;

    int array[5] = {1, 2, 3 ,4, 5};

    head = node_create(array + 0);

    if (head == NULL && *(int *) head->data != array[0])
        rc = -1;

    ck_assert_int_eq(rc, 0);

    free_list(&head);
}
END_TEST

START_TEST(list_create_ok)
{
    int rc = 0, n = 5;

    int array[5] = {1, 2, 3 ,4, 5};
    node_t *head = NULL;

    for (int i = 0; i < n && !rc; i++)
        rc = list_push(&head, array + i);

    if (rc != 0 || head == NULL)
        rc = -1;
    else
    {
        node_t *check_head = head;
        for (int i = 0; i < n && !rc; i++, check_head = check_head->next)
            if (*(int *) check_head->data != *(array + i))
                rc = -1;
    }

    ck_assert_int_eq(rc, 0);

    free_list(&head);
}
END_TEST

START_TEST(list_free_ok)
{
    int rc = 0, n = 5;
    node_t *head = node_create(&n);

    if (head == NULL)
        rc = -1;

    ck_assert_int_eq(rc, 0);

    free_list(&head);
}
END_TEST

START_TEST(list_free_ok_2)
{
    int rc = 0, n = 5;
    node_t *head = NULL;
    int array[5] = {1, 2, 3 ,4, 5};

    for (int i = 0; i < n && !rc; i++)
        rc = list_push(&head, array + i);
    free_list(&head);

    if (rc != 0 || head != NULL)
        rc = -1;
    ck_assert_int_eq(rc, 0);

    free_list(&head);
}
END_TEST

//neg
START_TEST(node_create_er)
{
    int rc = 0;
    node_t *head = NULL;

    head = node_create(NULL);
    if (head == NULL)
        rc = -1;

    ck_assert_int_eq(rc, -1);

    free_list(&head);
}
END_TEST

START_TEST(list_free_er_1)
{
    int rc = 0;
    node_t **head = NULL;

    free_list(head);
    if (head == NULL)
        rc = -1;

    ck_assert_int_eq(rc, -1);
}
END_TEST

START_TEST(list_free_er_2)
{
    int rc = 0;
    node_t *head = NULL;

    if (head == NULL)
        rc = -1;

    ck_assert_int_eq(rc, -1);

    free_list(&head);
}
END_TEST




Suite *memory_list_suite(void)
{
    Suite *s = suite_create("memory_list");

    TCase *tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, node_create_er);
    tcase_add_test(tc_neg, list_free_er_1);
    tcase_add_test(tc_neg, list_free_er_2);

    suite_add_tcase(s, tc_neg);

    TCase *tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, list_push_ok);
    tcase_add_test(tc_pos, node_create_ok);
    tcase_add_test(tc_pos, list_create_ok);
    tcase_add_test(tc_pos, list_free_ok);
    tcase_add_test(tc_pos, list_free_ok_2);

    suite_add_tcase(s, tc_pos);

    return s;
}