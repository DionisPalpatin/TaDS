#include "operations_with_list.h"
#include "operations_with_element_list.h"
#include <check_main.h>

//pos
START_TEST(comp_a_b)
{
    int a = 56, b = 68, rc = 0;
    int res = comparator(&a, &b);
    if (res != a - b)
        rc = -1;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(comp_b_a)
{
    int a = 56, b = 68, rc = 0;
    int res = comparator(&b, &a);
    if (res != b - a)
        rc = -1;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(comp_a_a)
{
    int a = 56, b = 56, rc = 0;
    int res = comparator(&a, &b);
    if (res != a - b)
        rc = -1;

    ck_assert_int_eq(rc, 0);
}
END_TEST


START_TEST(pop_front_ok)
{
    int *data = NULL;
    node_t *head = NULL;

    int element = 10, rc = 0;

    head = node_create(&element);

    data = pop_front(&head);
    if (head != NULL || *data != element)
        rc = -1;

    ck_assert_int_eq(rc, 0);

    free_list(&head);
}
END_TEST

START_TEST(pop_back_ok)
{
    int *data = NULL;
    node_t *head = NULL;

    int element = 10, rc = 0;

    head = node_create(&element);

    data = pop_back(&head);
    if (head != NULL || *data != element)
        rc = -1;

    ck_assert_int_eq(rc, 0);

    free_list(&head);
}
END_TEST

START_TEST(sort_ok)
{
    int elements[10] = {1, 5, 0, -1, 10, 9, -2, 11, 90, -90};
    int el_sort[10] = {-90, -2, -1, 0, 1, 5, 9, 10, 11, 90};
    int n = 10, rc = 0;
    node_t *head = NULL;

    for (int i = 0; i < n && !rc; i++)
        rc = list_push(&head, elements + i);

    if (rc != 0)
        rc = -1;
    else
    {
        head = sort(head, comparator);
        if (head == NULL)
            rc = -1;
        else
        {
            int check = 0;
            node_t *check_head = head;
            for (int i = 0; i < n && !check; i++, check_head = check_head->next)
                if (*(int *) check_head->data != *(el_sort + i))
                {
                    rc = -1;
                    check = 1;
                }
        }
    }
    free_list(&head);

    ck_assert_int_eq(rc, 0);
}
END_TEST



//neg

START_TEST(pop_front_er)
{
    int *data = NULL, rc = 0;

    data = pop_front(NULL);
    if (data == NULL)
        rc = -1;

    ck_assert_int_eq(rc, -1);
}

START_TEST(pop_back_er)
{
    int *data = NULL, rc = 0;

    data = pop_back(NULL);
    if (data == NULL)
        rc = -1;

    ck_assert_int_eq(rc, -1);
}

START_TEST(sort_empty)
{
    int rc = 0;
    node_t *head = NULL;
    head =sort(head, comparator);
    if (head == NULL)
        rc = -1;

    ck_assert_int_eq(rc, -1);
}

START_TEST(sort_er)
{
    int rc = 0, el = 10;
    node_t *head = node_create(&el);
    head =sort(head, NULL);
    if (head == NULL || *(int *) head->data == el)
        rc = -1;

    ck_assert_int_eq(rc, -1);
    free_list(&head);
}





Suite *list_operations_suite(void)
{
    Suite *s = suite_create("list_operations");

    TCase *tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, pop_front_er);
    tcase_add_test(tc_neg, pop_back_er);
    tcase_add_test(tc_neg, sort_empty);
    tcase_add_test(tc_neg, sort_er);

    suite_add_tcase(s, tc_neg);

    TCase *tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, comp_a_b);
    tcase_add_test(tc_pos, comp_b_a);
    tcase_add_test(tc_pos, comp_a_a);
    tcase_add_test(tc_pos, pop_front_ok);
    tcase_add_test(tc_pos, pop_back_ok);
    tcase_add_test(tc_pos, sort_ok);

    suite_add_tcase(s, tc_pos);

    return s;
}
