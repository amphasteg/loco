#include <stdio.h>
#include <string.h>
#include <tests.h>
#include "hostname.c"

int verify_hostname_test_success() {
  char hostname[6] = "TEST\0";
  return verify_hostname(hostname, 6);
}

int verify_hostname_test_truncated() {
  char hostname[5] = "TEST";
  int ret = verify_hostname(hostname, 5);
  if (ret != 0)
    return 0;

  return 1;
}

int verify_hostname_test_no_null_terminator() {
  char hostname[3] = "TES";
  int ret = verify_hostname(hostname, 3);

  if (ret != 0)
    return 0;

  return 1;
}

int get_hostname_success() {
  char *hostname = get_hostname();
  if (hostname == NULL)
    return 1;

  printf("Got host name: %s\n", hostname);
  return 0;
}

void run_hostname_test_suite() {
  struct test_suite *suite = create_test_suite(
      "hostname tests", strlen("hostname tests"));
  add_test(&verify_hostname_test_success,
           "success", strlen("success"), suite);
  add_test(&verify_hostname_test_truncated,
           "truncated", strlen("truncated"),
           suite);
  add_test(
      &verify_hostname_test_no_null_terminator,
      "no null terminator",
      strlen("no null terminator"), suite);
  add_test(&get_hostname_success,
           "get hostname success",
           strlen("get hostname success"), suite);
  run_tests(suite);
}
