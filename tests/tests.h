#include <stdio.h>
#ifndef TEST_HEADER
#define TEST_HEADER
#define ASSERT_INT_EQUAL(expected, actual)                                     \
  do {                                                                         \
    if (expected != actual) {                                                  \
      printf("ERROR: Expected %d, got %d instead at line %d\n", expected,      \
             actual, __LINE__);                                                \
      return 1;                                                               \
    }                                                                          \
    return 0;                                                                  \
  } while (0);

#define malloc mock_malloc

void set_mock_malloc_errno(int);
void *mock_malloc(size_t);
#endif

