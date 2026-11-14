#include <testing_functions.h>
#include <testing_mocks.h>

#ifdef LOCO_TESTING_MOCKS
#include <test_macros.h>
#endif

#ifndef LOCO_TESTS
#define LOCO_TESTS
#define ASSERT_INT_EQUAL(n1, n2)                                               \
  if (n1 != n2)                                                                \
  return 1

#define ASSERT_INT_NOT_EQUAL(n1, n2)                                           \
  if (n1 == n2)                                                                \
  return 1


#define ASSERT_PTR_NOT_NULL(p1)                                           \
  if (p1 == NULL)                                                                \
    return 1


#define ASSERT_PTR_NULL(p1)                                           \
  if (p1 != NULL)                                                                \
    return 1

#define ADD_TEST(func) add_test(func, #func, strlen(#func), suite)

#define CREATE_SUITE(name)                                                     \
  struct test_suite *suite = create_test_suite(#name, strlen(#name))

#define RUN_TESTS() run_tests(suite)
#endif
