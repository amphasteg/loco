#include <stdlib.h>
#define MOCK_IMPL <addrinfo.c>
#include <tests.h>

int set_hints_success(void) {
  struct addrinfo *hints =
      malloc(sizeof(struct addrinfo));

  if (hints == NULL) {
    fputs("Test failed, unable to allocate memory for hints.\n", stderr);
    return 1;
  }

  set_hints(hints, IP_BOTH);

  ASSERT_INT_EQUAL(hints->ai_family,
                   AF_UNSPEC);
  ASSERT_INT_EQUAL(hints->ai_protocol,
                   IPPROTO_TCP);
  ASSERT_INT_EQUAL(hints->ai_socktype,
                   SOCK_STREAM);
  ASSERT_INT_EQUAL(hints->ai_flags,
                   AI_PASSIVE);

  free(hints);

  return 0;
}

int set_null_hints(void) {
  struct addrinfo *hints = NULL;

  set_hints(hints, IP_BOTH);
  ASSERT_PTR_NULL(hints);

  return 0;
}

int set_hints_enum_out_of_range(void) {
  struct addrinfo *hints = malloc(sizeof(struct addrinfo));

  if (hints == NULL) {
    fputs("Test failed, unable to allocate memory for hints.\n", stderr);
    return 1;
  }

  set_hints(hints, 34);

  ASSERT_INT_EQUAL(hints->ai_family, AF_UNSPEC);

  free(hints);

  return 0;
}

int get_address_info_success(void) {
  struct addrinfo *hints =
      malloc(sizeof(struct addrinfo));
  struct addrinfo *address_info = malloc(sizeof(struct addrinfo));
  int port = 0;

  if (hints == NULL || address_info == NULL) {
    fputs("Test failed, unable to allocate memory for hints.\n", stderr);
    return 1;
}

  WSA_STARTUP();

  set_hints(hints, IP_BOTH);

  get_address_info(address_info, hints, port);

  ASSERT_PTR_NOT_NULL(address_info);

  WSA_CLEANUP();

  return 0;
}

void run_addrinfo_test_suite(void) {
  CREATE_SUITE(Addrinfo);

  ADD_TEST(set_hints_success);
  ADD_TEST(set_null_hints);
  ADD_TEST(set_hints_enum_out_of_range);
  ADD_TEST(get_address_info_success);

  RUN_TESTS();
}
