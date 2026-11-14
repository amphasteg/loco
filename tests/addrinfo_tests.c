#include <stdlib.h>
#define MOCK_IMPL <addrinfo.c>
#include <tests.h>

int set_hints_success() {
  struct addrinfo *addrinfo =
      malloc(sizeof(struct addrinfo));

  set_hints(addrinfo, IP_BOTH);

  ASSERT_INT_EQUAL(addrinfo->ai_family,
                   AF_UNSPEC);
  ASSERT_INT_EQUAL(addrinfo->ai_protocol,
                   IPPROTO_TCP);
  ASSERT_INT_EQUAL(addrinfo->ai_socktype,
                   SOCK_STREAM);
  ASSERT_INT_EQUAL(addrinfo->ai_flags,
                   AI_PASSIVE);

  return 0;
}

void run_addrinfo_test_suite(void) {
  CREATE_SUITE(Addrinfo);

  ADD_TEST(set_hints_success);

  RUN_TESTS();
}
