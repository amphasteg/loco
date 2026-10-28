#ifndef LOCO_TESTING_FUNCS
#define LOCO_TESTING_FUNCS

void set_mock_malloc_errno(int errnum);
void *mock_malloc(unsigned long ptr);
int assert_int_equal(int expected, int actual);
void add_test(int (*func)(void), const char *name, int name_len);
int run_test_by_index(int index);
int run_test_by_name(const char *name, int name_len);
/** Run all tests until list is exhausted, or one fails */
int run_all_tests(void);
/** Takes the arguments passed by main and determines to run test by index or by
 * name. Intended to be directly invoked by `main`.*/
int run_tests_by_arg(int argc, char *argv[]);

#endif
