#include <stdio.h>
#include <string.h>

#define MOCK_IMPL <hostname.c>
#include <tests.h>

int verify_hostname_test_success(void) {
  char hostname[6] = "TEST\0";
  int ret = verify_hostname(hostname, 6);

  ASSERT_INT_NOT_ZERO(ret);

  printf("Hostname size = %d\n", ret);

  END_TEST();
}

int verify_hostname_test_truncated(void) {
  char hostname[5] = "TEST";
  int response = verify_hostname(hostname, 5);

  ASSERT_INT_ZERO(response);

  END_TEST();
}

int verify_hostname_test_no_null_terminator(
    void) {
  char hostname[3] = "TES";
  int res = verify_hostname(hostname, 3);

  ASSERT_INT_ZERO(res);

  END_TEST();
}

int get_hostname_success(void) {
  set_gethostname_mocks(0, "hostname",
                        strlen("hostname"));
  struct string *hostname = get_hostname();

  ASSERT_PTR_NOT_NULL(hostname);

  printf("Got host name: %s\n", hostname->string);
  free(hostname);

  END_TEST();
}

int get_hostname_malloc_fail(void) {
  set_mock_malloc_errno(1);
  struct string *hostname = get_hostname();
  ASSERT_PTR_NULL(hostname);

  free(hostname);
  END_TEST();
}

int get_hostname_gethostname_fails(void) {
  set_gethostname_mocks(1, NULL, 0);
  struct string *hostname = get_hostname();
  ASSERT_PTR_NULL(hostname);

  free(hostname);
  END_TEST();
}

void run_hostname_test_suite(void) {
  CREATE_SUITE("Hostname Tests");

  ADD_TEST(verify_hostname_test_success);
  ADD_TEST(verify_hostname_test_truncated);
  ADD_TEST(verify_hostname_test_no_null_terminator);
  ADD_TEST(get_hostname_success);
  ADD_TEST(get_hostname_malloc_fail);
  ADD_TEST(get_hostname_gethostname_fails);

  RUN_TESTS();
}
