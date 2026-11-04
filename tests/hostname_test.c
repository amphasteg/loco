#include "testing_mocks.h"
#include <errno.h>
#define MOCK_IMPL <hostname.c>

#include <stdio.h>
#include <string.h>
#include <tests.h>

int verify_hostname_test_success(void) {
  char hostname[6] = "TEST\0";
  int ret = verify_hostname(hostname, 6);
  if (ret != 0) {
    printf("Hostname size = %d\n", ret);
    return 0;
  }

  return 1;
}

int verify_hostname_test_truncated(void) {
  char hostname[5] = "TEST";
  return verify_hostname(hostname, 5);
}

int verify_hostname_test_no_null_terminator(
    void) {
  char hostname[3] = "TES";
  return verify_hostname(hostname, 3);
}

int get_hostname_success(void) {
  set_gethostname_mocks(0, "hostname",
                        strlen("hostname"));
  char *hostname = get_hostname();
  if (hostname == NULL)
    return 1;

  printf("Got host name: %s\n", hostname);
  return 0;
}

int get_hostname_malloc_fail(void) {
  set_mock_malloc_errno(1);
  char *hostname = get_hostname();
  if (hostname == NULL && errno == 1)
    return 0;
  return 1;
}

int get_hostname_gethostname_fails(void) {
  set_gethostname_mocks(1, NULL, 0);
  char *hostname = get_hostname();
  if (hostname == NULL && errno == 1)
    return 0;
  return 1;
}

void run_hostname_test_suite(void) {
  struct test_suite *suite = create_test_suite(
      "hostname tests", strlen("hostname tests"));

  add_test(verify_hostname_test_success,
           "success", strlen("success"), suite);

  add_test(verify_hostname_test_truncated,
           "truncated", strlen("truncated"),
           suite);

  add_test(
      verify_hostname_test_no_null_terminator,
      "no null terminator",
      strlen("no null terminator"), suite);

  add_test(get_hostname_success,
           "get hostname success",
           strlen("get hostname success"), suite);

  add_test(get_hostname_malloc_fail,
           "malloc fails", strlen("malloc fails"),
           suite);

  add_test(get_hostname_gethostname_fails,
           "gethostname fails",
           strlen("gethostname fails"), suite);

  run_tests(suite);
}
