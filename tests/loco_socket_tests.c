#include <stdlib.h>
#define MOCK_IMPL <loco_socket.c>
#include <tests.h>

int increment_list_success() {
  struct listening_sock_list *list =
      initialize_socket_list();

  int success_value = increment_list_size(list);

  free(list);

  ASSERT_INT_EQUAL(success_value, 1);

  return 0;
}

int increment_list_realloc_fail() {
  struct listening_sock_list *list =
      initialize_socket_list();

  set_realloc_errno(ENOMEM);

  int response_value = increment_list_size(list);

  ASSERT_INT_EQUAL(response_value, -1);

  return 0;
}

int increment_list_null_list() {
  struct listening_sock_list *list = NULL;

  int response_value = increment_list_size(list);

  ASSERT_INT_EQUAL(response_value, -1);

  return 0;
}

void run_socket_test_suite(void) {
  CREATE_SUITE(Loco Socket Tests);

  ADD_TEST(increment_list_success);
  ADD_TEST(increment_list_realloc_fail);
  ADD_TEST(increment_list_null_list);

  RUN_TESTS();
}
