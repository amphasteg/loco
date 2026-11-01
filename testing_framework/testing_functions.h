#ifndef LOCO_TESTING_FUNCS
#define LOCO_TESTING_FUNCS

void set_mock_malloc_errno(int errnum);
void *mock_malloc(unsigned long ptr);
void add_test(int (*func)(void), const char *name, int name_len);
/** Run all tests until list is exhausted, or one fails */
int run_tests(void);
/** Takes the arguments passed by main and determines to run test by index or by
 * name. Intended to be directly invoked by `main`.*/
int run_tests_by_arg(int argc, char *argv[]);

#endif
