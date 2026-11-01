#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <terminal_color.h>
#include <testing_functions.h>
#include <time.h>

struct test {
  int name_len;
  int (*function)(void);
  char *test_name;
  struct test *next;
};

struct test_suite {
  int name_len;
  char *suite_name;
  struct test *test_list;
};

struct test_suite *
create_test_suite(const char *suite_name,
                  int name_len) {
  struct test_suite *new_test_suite =
      malloc(sizeof(struct test_suite));
  new_test_suite->name_len = name_len;
  new_test_suite->suite_name = strndup(
      suite_name,
      name_len + 1); //+1 for null terminator
  new_test_suite->test_list = NULL;
  return new_test_suite;
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
              int name_length,
              struct test_suite *suite) {
  if (suite == NULL) {
    fputs("Testing suite supplied is null.\n",
          stderr);
    return;
  }

  if (name == NULL) {
    fputs("No name was entered for test. Will "
          "`null` in place",
          stderr);
    name = malloc(sizeof(char) * 5);
    name = "null";
    name_length = 4;
  }

  if (suite->test_list == NULL) {
    create_test(func, name, name_length,
                &(suite->test_list));
    return;
  }

  struct test *last_test;

  for (last_test = suite->test_list;
       last_test->next != NULL;
       last_test = suite->test_list->next)
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

int run_tests(struct test_suite *suite) {
  int test_num = 0;
  int test_successes = 0;
  int ret = 0;

  if (suite == NULL) {
    fputs("Testing suite is null.", stderr);
    return 1;
  }

  if (suite->test_list == NULL) {
    fputs("No tests were added! Add some tests "
          "using the function `add_test`.\n",
          stderr);
    return 1;
  }

  printf("Running tests suite: %s\n", suite->suite_name);

  for (struct test *unit_test = suite->test_list;
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
