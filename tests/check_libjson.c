#include <stdlib.h>
#include <check.h>

extern Suite* till_eos_suite(void);
extern Suite* json_items_create_suite(void);

static Suite* (*suiters[])(void) = {
    till_eos_suite,
    json_items_create_suite,
    NULL
};

int
main(void)
{
    int total_number_of_failures = 0;

    for (unsigned int i=0; suiters[i] != NULL; i++) {
        Suite*   suite = suiters[i]();
        SRunner* run   = srunner_create(suite);

        srunner_run_all(run, CK_NORMAL);
        total_number_of_failures += srunner_ntests_failed(run);
        srunner_free(run);
    }

    return (total_number_of_failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
