#include "loco_response_codes.h"
#include <wsa.h>
#ifndef WIN32
#include <arpa/inet.h>
#endif
#include <stdlib.h>
#define MOCK_IMPL <addrinfo.c>
#include <tests.h>

int build_hints_for_tests(
    struct addrinfo **hints,
    struct addrinfo **info) {
  *hints = malloc(sizeof(struct addrinfo));
  *info = malloc(sizeof(struct addrinfo));

  if (*hints == NULL || *info == NULL) {
    fputs("Test failed, unable to allocate "
          "memory for hints.\n",
          stderr);
    return 1;
  }

  set_hints(*hints, IP_BOTH);

  return 0;
}

int set_hints_success(void) {
  struct addrinfo *hints =
      malloc(sizeof(struct addrinfo));

  if (hints == NULL) {
    fputs("Test failed, unable to allocate "
          "memory for hints.\n",
          stderr);
    return ALLOC_ERROR;
    ;
  }

  set_hints(hints, IP_BOTH);

  ASSERT_INT_EQUAL(hints->ai_family, AF_UNSPEC);
  ASSERT_INT_EQUAL(hints->ai_protocol,
                   IPPROTO_TCP);
  ASSERT_INT_EQUAL(hints->ai_socktype,
                   SOCK_STREAM);
  ASSERT_INT_EQUAL(hints->ai_flags, AI_PASSIVE);

  free(hints);

  END_TEST();
}

int set_null_hints(void) {
  struct addrinfo *hints = NULL;

  set_hints(hints, IP_BOTH);
  ASSERT_PTR_NULL(hints);

  END_TEST();
}

int set_hints_enum_out_of_range(void) {
  struct addrinfo *hints =
      malloc(sizeof(struct addrinfo));

  if (hints == NULL) {
    fputs("Test failed, unable to allocate "
          "memory for hints.\n",
          stderr);
    return ALLOC_ERROR;
  }

  set_hints(hints, 34);

  ASSERT_INT_EQUAL(hints->ai_family, AF_UNSPEC);

  free(hints);

  END_TEST();
}

int get_address_info_success(void) {

  struct addrinfo *hints, *address_info;

  ASSERT_INT_EQUAL(build_hints_for_tests(
                       &hints, &address_info),
                   0);

  int result =
      get_address_info(&address_info, hints);

  ASSERT_INT_ZERO(result);
  ASSERT_PTR_NOT_NULL(address_info);
  ASSERT_PTR_NOT_NULL(address_info->ai_addr);
  ASSERT_INT_NOT_ZERO(address_info->ai_addrlen);

  char address[INET6_ADDRSTRLEN];
  void *ip;

  puts("Returned IP addresses:\n");

  for (struct addrinfo *p = address_info;
       p != NULL; p = p->ai_next) {
    if (p->ai_family == AF_INET) {
      struct sockaddr_in *ipv4 =
          (struct sockaddr_in *)p->ai_addr;
      ip = &(ipv4->sin_addr);
    } else {
      struct sockaddr_in6 *ipv6 =
          (struct sockaddr_in6 *)p->ai_addr;
      ip = &(ipv6->sin6_addr);
    }

    inet_ntop(p->ai_family, ip, address,
              INET6_ADDRSTRLEN);

    printf("%s\n", address);
  }

  puts("\n");

  END_TEST();
}

int get_address_info_production_success(void) {
  struct addrinfo *hints, *address_info;

  ASSERT_INT_EQUAL(build_hints_for_tests(
                       &hints, &address_info),
                   0);

  int result =
      get_address_info(&address_info, hints);

  ASSERT_INT_ZERO(result);
  ASSERT_PTR_NOT_NULL(address_info);
  ASSERT_PTR_NOT_NULL(address_info->ai_addr);
  ASSERT_INT_NOT_ZERO(address_info->ai_addrlen);

  char address[INET6_ADDRSTRLEN];
  void *ip;

  puts("Returned IP addresses:\n");

  for (struct addrinfo *p = address_info;
       p != NULL; p = p->ai_next) {
    if (p->ai_family == AF_INET) {
      struct sockaddr_in *ipv4 =
          (struct sockaddr_in *)p->ai_addr;
      ip = &(ipv4->sin_addr);
    } else {
      struct sockaddr_in6 *ipv6 =
          (struct sockaddr_in6 *)p->ai_addr;
      ip = &(ipv6->sin6_addr);
    }

    inet_ntop(p->ai_family, ip, address,
              INET6_ADDRSTRLEN);

    printf("%s\n", address);
  }

  puts("\n");

  END_TEST();
}

int get_address_info_fails() {
  struct addrinfo *hints, *address_info;
  int errnumber = 23;

  ASSERT_INT_EQUAL(build_hints_for_tests(
                       &hints, &address_info),
                   0);

  set_getaddrinfo_errno(errnumber);
  int result =
      get_address_info(&address_info, hints);

  ASSERT_INT_NOT_ZERO(result);
  ASSERT_INT_EQUAL(result, errnumber);
  ASSERT_PTR_NULL(address_info);

  END_TEST();
}

void run_addrinfo_test_suite(void) {
  CREATE_SUITE("Addrinfo");

  ADD_TEST(set_hints_success);
  ADD_TEST(set_null_hints);
  ADD_TEST(set_hints_enum_out_of_range);
  ADD_TEST(get_address_info_success);
  ADD_TEST(get_address_info_fails);
  ADD_TEST(get_address_info_production_success);

  initialize_wsa();
  RUN_TESTS();
  wsa_cleanup();
}
