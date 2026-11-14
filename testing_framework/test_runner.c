#define RUN_SUITE(suite_runner) \
  void suite_runner(); \
  suite_runner()

int main(void) {
  RUN_SUITE(run_hostname_test_suite);
  RUN_SUITE(run_socket_test_suite);
  RUN_SUITE(run_addrinfo_test_suite);
}
