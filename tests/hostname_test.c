#include "hostname.c"
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <tests.h>

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

int main(int argc, char *argv[]) {
  add_test(&verify_hostname_test_success,
           "success", strlen("success"));
  add_test(&verify_hostname_test_truncated,
           "truncated", strlen("truncated"));
  add_test(
      &verify_hostname_test_no_null_terminator,
      "no null terminator",
      strlen("no null terminator"));
  run_tests();
}
