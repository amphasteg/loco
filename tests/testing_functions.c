#include <_ctype.h>
#include <_stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <testing_functions.h>
#include <time.h>
#define NORMAL 0

#undef malloc

struct test {
  int name_len;
  int (*function)(void);
  char *test_name;
  struct test *next;
};

int mock_malloc_errno = 0;
struct test *added_tests = NULL;

void *mock_malloc(size_t size) {
  if (mock_malloc_errno == 0)
    return malloc(size);

  errno = mock_malloc_errno;
  return NULL;
}

void set_mock_malloc_errno(int error) {
  mock_malloc_errno = error;
}

int assert_int_equal(int expected, int actual) {
  if (expected != actual) {
    printf("ERROR: Expected %d, got %d instead "
           "at line %d\n",
           expected, actual, __LINE__);
    return 1;
  }
  return 0;
}

struct test *create_test(int (*func)(void),
                         const char *name,
                         int name_len) {
  struct test *new_test =
      malloc(sizeof(struct test));
  new_test->function = func;
  new_test->next = NULL;
  new_test->name_len = name_len;
  int test_name_size =
      (name_len + 1) * sizeof(char);
  new_test->test_name = malloc(test_name_size);
  strncpy(new_test->test_name, name,
          test_name_size);
  new_test->test_name[name_len] = '\0';

  return new_test;
}

void add_test(int (*func)(void), const char *name,
              int name_length) {
  struct test *next_test;
  for (struct test *next_test = added_tests;
       next_test != NULL;
       next_test = added_tests->next)
    ;

  next_test =
      create_test(func, name, name_length);
}

int run_timed_test(struct test *selected_test) {
  clock_t start, end;
  start = clock();
  int result = selected_test->function();
  end = clock();

  double time =
      (double)(end - start) / CLOCKS_PER_SEC;
  printf("Test %s executed in %f second\n",
         selected_test->test_name, time);
  return result;
}

int run_test_by_index(int index) {
  struct test *test_to_run = added_tests;

  int i = index;
  while (i != 0 && test_to_run != NULL) {
    test_to_run = test_to_run->next;
    i--;
  }

  if (test_to_run == NULL) {
    fprintf(
        stderr,
        "The test provided %d was not found.\n",
        index);
    return 1;
  }

  return run_timed_test(test_to_run);
}

struct test *find_test_by_name(const char *name,
                               int name_len) {
  struct test *test_to_run = added_tests;
  int len;

  while (test_to_run != NULL) {
    if (test_to_run->name_len > name_len)
      len = name_len;
    else
      len = test_to_run->name_len;

    if (strncmp(name, test_to_run->test_name,
                len) == 0)
      break;

    test_to_run = test_to_run->next;
  }

  return test_to_run;
}

int run_test_by_name(const char *name,
                     int name_len) {
  struct test *test_to_run =
      find_test_by_name(name, name_len);

  if (test_to_run == NULL) {
    fprintf(
        stderr,
        "The test provided %s was not found.\n",
        name);
    return 1;
  }

  return run_timed_test(test_to_run);
}

int run_all_tests(void) {
  struct test *unit_test;
  int test_num = 1;
  int ret = 0;

  for (unit_test = added_tests; unit_test != NULL;
       unit_test = unit_test->next) {
    printf("Running test %d:%s\n", test_num,
           unit_test->test_name);

    ret = run_timed_test(unit_test);

    if (ret != 0) {
      fprintf(stderr,
              "Test \"%s\" (#%d) returned %d\n",
              unit_test->test_name, test_num,
              ret);
      return ret;
    }

    test_num++;
  }

  return ret;
}


int run_tests_by_arg(int argc, char *argv[]) {
  if (argc > 2)
    printf(
        "Function '%s' only takes one argument (aside "
        "from program name). Will proceed with "
        "test using argument: %s.\n", __func__,
        argv[1]);

  int arg_len = strlen(argv[1]);
  char *str_end = malloc(sizeof(char) * arg_len);
  int index = strtol(argv[1], &str_end, 10);

  if ((index == 0 && errno == EINVAL) || str_end != NULL)
    return run_test_by_name(argv[1], arg_len);

  return run_test_by_index(index);
}
