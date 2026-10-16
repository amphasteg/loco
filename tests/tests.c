#include "tests.h"
#include <stdlib.h>
#define NORMAL 0

int mock_malloc_errno = 0;

void *mock_malloc(size_t size) {
  if (mock_malloc_errno == 0)
    return malloc(size);
  
  errno = mock_malloc_errno;
  return NULL;
}

void set_mock_malloc_errno(int error) {
  mock_malloc_errno = error;
}
