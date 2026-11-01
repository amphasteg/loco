#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <testing_mocks.h>

int mock_malloc_errno = 0;
struct test *added_tests = NULL;

void *mock_malloc(size_t size) {
  if (mock_malloc_errno == 0)
    return malloc(size);

  errno = mock_malloc_errno;
  return NULL;
}

void set_mock_malloc_errno(int error) {
  mock_malloc_errno = error;
}

int assert_int_equal(int expected, int actual) {
  if (expected != actual) {
    printf("ERROR: Expected %d, got %d instead "
           "at line %d\n",
           expected, actual, __LINE__);
    return 1;
  }
  return 0;
}
