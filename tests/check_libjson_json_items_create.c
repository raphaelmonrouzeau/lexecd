#include <check.h>
#include "../src/libjson/json.h"

START_TEST(test_fails_with_0_items)
{
    struct json_items* json_items = json_items_create(0);
    fail_unless(json_items == NULL);
}
END_TEST

START_TEST(test_10_items)
{
    struct json_items* json_items = json_items_create(10);
    fail_unless(json_items->items[0].value.next == 0);
    fail_unless(json_items->length == 10);
}
END_TEST

Suite*
json_items_create_suite(void)
{
    Suite* s = suite_create("json_items_create");
    TCase* tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_fails_with_0_items);
    tcase_add_test(tc_core, test_10_items);
    suite_add_tcase(s, tc_core);
    return s;
}
