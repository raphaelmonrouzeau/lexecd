#include <stdlib.h>
#include <check.h>
#include "../src/libjson/till_eos.h"

START_TEST(test_empty_string)
{
    char         s[1] = "\"";
    unsigned int i = 0;
    unsigned int m = sizeof(s);
    char         dst[128];
    unsigned int j = 0;
    unsigned int n = sizeof(dst);

    unsigned int r = till_eos(s, i, m, dst, &j, n);

    fail_unless(j == m-1);
    fail_unless(r == m-1);
}
END_TEST

START_TEST(test_one_null_character)
{
    char         s[2] = "\0\"";
    unsigned int i = 0;
    unsigned int m = sizeof(s);
    char         dst[128];
    unsigned int j = 0;
    unsigned int n = sizeof(dst);

    unsigned int r = till_eos(s, i, m, dst, &j, n);

    fail_unless(j == m-1);
    fail_unless(r == m-1);
    fail_unless(memcmp(s,dst,m-1) == 0);
}
END_TEST

START_TEST(test_null_ctrlA_null_crtlB_null)
{
    const char   s[6] = "\0\0\0\"";
    unsigned int i = 0;
    unsigned int m = sizeof(s);
    char         dst[128];
    unsigned int j = 0;
    unsigned int n = sizeof(dst);

    unsigned int r = till_eos(s, i, m, dst, &j, n);

    fail_unless(j == m-1);
    fail_unless(r == m-1);
    fail_unless(memcmp(s,dst,m-1) == 0);
}
END_TEST

START_TEST(test_shorter_s)
{
    char         s[43] = "simplyANotSoButStillNonethelessLongKeyname\"";
    unsigned int i = 0;
    unsigned int m = sizeof(s)-5;
    char         dst[128];
    unsigned int j = 0;
    unsigned int n = sizeof(dst);

    unsigned int r = till_eos(s, i, m, dst, &j, n);

    fail_unless(j == m);
    fail_unless(r == m);
    fail_unless(memcmp(s,dst,m-1) == 0);
}
END_TEST

START_TEST(test_shorter_dst)
{
    char         s[43] = "simplyANotSoButStillNonethelessLongKeyname\"";
    unsigned int i = 0;
    unsigned int m = sizeof(s);
    char         dst[m-6];
    unsigned int j = 0;
    unsigned int n = sizeof(dst);

    unsigned int r = till_eos(s, i, m, dst, &j, n);

    fail_unless(j == n);
    fail_unless(r == n);
    fail_unless(memcmp(s,dst,n-1) == 0);
}
END_TEST

Suite*
suite(void)
{
    Suite* s = suite_create("till_eos");
    TCase* tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_empty_string);
    tcase_add_test(tc_core, test_one_null_character);
    tcase_add_test(tc_core, test_null_ctrlA_null_crtlB_null);
    tcase_add_test(tc_core, test_shorter_s);
    tcase_add_test(tc_core, test_shorter_dst);
    suite_add_tcase(s, tc_core);
    return s;
}

int
main(void)
{
    int number_failed;
    Suite *s = suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
