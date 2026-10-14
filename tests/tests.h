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
#endif
