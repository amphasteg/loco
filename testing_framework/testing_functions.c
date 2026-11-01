#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <testing_functions.h>
#include <terminal_color.h>
#include <time.h>

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

void create_test(int (*func)(void),
                 const char *name, int name_len,
                 struct test **new_test) {
  *new_test = malloc(sizeof(struct test));

  if (*new_test == NULL)
    fprintf(stderr, "Failed to assign memory for "
                    "testing structure.\n");

  (*new_test)->name_len = name_len;

  (*new_test)->function = malloc(sizeof(*func));
  if ((*new_test)->function == NULL) {
    fprintf(stderr, "Failed to allocate memory "
                    "for test function.\n");
    free(*new_test);
  }

  (*new_test)->function = func;

  (*new_test)->next = NULL;

  int test_name_len = name_len + 1;
  int test_name_size =
      test_name_len * sizeof(char);
  (*new_test)->test_name = malloc(test_name_size);
  if ((*new_test)->test_name == NULL) {
    fprintf(stderr, "Failed to assign memory for "
                    "test name.\n");
    free(*new_test);
  }

  strncpy((*new_test)->test_name, name,
          test_name_len);
  (*new_test)->test_name[name_len] = '\0';
  (*new_test)->name_len = name_len;
}

void add_test(int (*func)(void), const char *name,
              int name_length) {
  if (added_tests == NULL) {
    create_test(func, name, name_length,
                &added_tests);
    return;
  }

  struct test *last_test;

  for (last_test = added_tests;
       last_test->next != NULL;
       last_test = added_tests->next)
    ;

  create_test(func, name, name_length,
              &(last_test->next));
}

int run_timed_test(struct test *selected_test) {
  clock_t start, end;
  start = clock();
  int result = selected_test->function();
  end = clock();

  double time =
      ((double)(end - start) / CLOCKS_PER_SEC) *
      1000.0;
  printf("Execution time %fms\n", time);
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

int print_test_results(int tests_ran,
                       int test_successes) {
  fputs("Tests passed: ", stdout);
  float success_percentage =
      ((float)test_successes / tests_ran) * 100.0;
  float percent_threshold = 80.0;

  if (success_percentage < 100.0) {
    if (success_percentage < percent_threshold)
      print_colored_text(RED, "%.3g%%\n",
                         success_percentage);
    else
      print_colored_text(YELLOW, "%.3g%%\n",
                         success_percentage);

    return 1;
  }

  print_colored_text(GREEN, "%.3g%%\n",
                     success_percentage);

  return 0;
}

int run_tests(void) {
  int test_num = 0;
  int test_successes = 0;
  int ret = 0;

  if (added_tests == NULL) {
    fputs("No tests were added! Add some tests "
          "using the function `add_test`.\n",
          stderr);
    return 1;
  }

  for (struct test *unit_test = added_tests;
       unit_test != NULL;
       unit_test = unit_test->next) {
    test_num++;
    char *test_header;
    puts("---------------------");
    printf("Test #%d: \"%s\"\n", test_num,
           unit_test->test_name);
    puts("---------------------");

    if ((ret = run_timed_test(unit_test)) != 0) {
      print_colored_text(RED, "FAILURE!\n");
      printf("Returned non-zero exit code: %d\n",
             ret);
    } else {
      print_colored_text(GREEN, "SUCCESS!\n");
      test_successes++;
    }
  }

  return print_test_results(test_num,
                            test_successes);
}
