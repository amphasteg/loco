#include <tests.h>
extern void run_hostname_test_suite();
void run_socket_test_suite();

int main(void) {
  run_hostname_test_suite();
  run_socket_test_suite();
}
