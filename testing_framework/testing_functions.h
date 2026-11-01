#ifndef LOCO_TESTING_FUNCS
#define LOCO_TESTING_FUNCS

struct test_suite;

/**Adds a new test to the supplied testing suite*/
void add_test(int (*func)(void), const char *name, int name_len, struct test_suite *suite);
/**Creates a new testing_suite with a defined name*/
struct test_suite *create_test_suite(const char* suite_name, int name_len);
/**Runs all tests in given testing suite*/
int run_tests(struct test_suite *suite);

#endif
