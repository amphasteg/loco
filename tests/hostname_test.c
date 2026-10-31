#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <tests.h>
#include "hostname.c"

int verify_hostname_test_success() {
  char hostname[6] = "BOOM\0";
  return verify_hostname(hostname, 6);
}

int verify_hostname_test_truncated() {
  char hostname[5] = "BOOM";
  int ret = verify_hostname(hostname, 5);
  if (ret != 0) {
    printf("Return value: %d\n", ret);
    return 0;
  }

  return 1;
}

int main(int argc, char* argv[]) {
  add_test(&verify_hostname_test_success, "success", strlen("success"));
  add_test(&verify_hostname_test_truncated, "truncated", strlen("truncated"));
  run_all_tests();
}
