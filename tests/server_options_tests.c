#include "loco_response_codes.h"
#include <sys/errno.h>
#define MOCK_IMPL <server_options.c>
#include <tests.h>

int server_options_init_success(void) {
  struct server_options *options =
      initialize_server_options();

  ASSERT_PTR_NOT_NULL(options);

  free(options);

  END_TEST();
}

int server_options_malloc_fail(void) {
  set_mock_malloc_errno(ENOMEM);
  struct server_options *options =
      initialize_server_options();

  ASSERT_PTR_NULL(options);

  free(options);

  END_TEST();
}

int set_ip_type_success(void) {
  struct server_options *options =
      initialize_server_options();

  ASSERT_PTR_NOT_NULL(options);

  int res = set_ip_type(options, IPV4);

  ASSERT_INT_EQUAL(options->ip_type, IPV4);
  ASSERT_INT_EQUAL(res, LOCO_SUCCESS);

  END_TEST();
}

int set_ip_type_null(void) {
  struct server_options *options = NULL;

  ASSERT_PTR_NULL(options);

  int ret = set_ip_type(options, IPV4);

  ASSERT_INT_EQUAL(ret, PROVIDED_NULL);

  END_TEST();
}

int set_ip_type_out_of_range(
    void) {
  struct server_options *options =
      initialize_server_options();

  ASSERT_PTR_NOT_NULL(options);

  int res = set_ip_type(options, IPV6 + 1);

  ASSERT_INT_EQUAL(options->ip_type, IP_BOTH);
  ASSERT_INT_EQUAL(res, ENUM_OUT_OF_RANGE);

  END_TEST();
}

void run_server_options_suite(void) {
  CREATE_SUITE("Server Options");

  ADD_TEST(server_options_init_success);
  ADD_TEST(server_options_malloc_fail);
  ADD_TEST(set_ip_type_success);
  ADD_TEST(set_ip_type_null);
  ADD_TEST(set_ip_type_out_of_range);

  RUN_TESTS();
}
