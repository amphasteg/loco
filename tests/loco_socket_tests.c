#include <stdlib.h>

#define MOCK_IMPL <loco_socket.c>
#include <tests.h>

int increment_list_success() {
  struct listening_sock_list *list =
      malloc(sizeof(struct listening_sock_list));
  list->list_size = 0;
  list->socket_item = NULL;

  int success_value = increment_list_size(list);

  if (success_value != 1 && success_value != 0)
    return success_value;

  return 0;
}

void run_socket_test_suite(void) {
  struct test_suite *suite = create_test_suite(
      "Loco Socket Tests",
      strlen("Loco Socket Tests"));

  add_test(increment_list_success,
           "Increment List Success",
           strlen("Increment List Success"),
           suite);

  run_tests(suite);
}
