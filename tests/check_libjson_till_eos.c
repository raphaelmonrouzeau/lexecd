#include <stdlib.h>
#include <check.h>
#include "../src/libjson/till_eos.h"

START_TEST(test_till_eos_empty_string)
{
    char         s[] = "\"";
    unsigned int i = 0;
    unsigned int m = 1;
    char         dst[128];
    unsigned int j = 0;
    unsigned int n = 128;

    unsigned int r = till_eos(s, i, m, dst, &j, n);

    fail_unless(j == 0);
    fail_unless(r == 1);
}
END_TEST

START_TEST(test_till_eos_one_null_character)
{
    char         s[] = "\0\"";
    unsigned int i = 0;
    unsigned int m = 2;
    char         dst[128];
    unsigned int j = 0;
    unsigned int n = 128;

    unsigned int r = till_eos(s, i, m, dst, &j, n);

    fail_unless(j == 1);
    fail_unless(r == 1);
    fail_unless(dst[0] == '\0');
}
END_TEST

Suite*
till_eos_suite(void)
{
    Suite* s = suite_create("till_eos");
    TCase* tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_till_eos_empty_string);
    tcase_add_test(tc_core, test_till_eos_one_null_character);
    suite_add_tcase(s, tc_core);
    return s;
}

int
main(void)
{
    int number_failed;
    Suite *s = till_eos_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
