#ifndef LOCO_TESTS
#define LOCO_TESTS

#include <loco_response_codes.h>
#include <string.h>
#include <testing_functions.h>
#include <testing_mocks.h>

#ifdef LOCO_TESTING_MOCKS
#include <mock_replacements.h>
#endif

#define ASSERT_INT_EQUAL(n1, n2)                                               \
  if (n1 != n2)                                                                \
  return LOCO_FAIL

#define ASSERT_INT_NOT_EQUAL(n1, n2)                                           \
  if (n1 == n2)                                                                \
  return LOCO_FAIL

#define ASSERT_INT_NOT_ZERO(n)                                                 \
  if (n == 0)                                                                  \
  return LOCO_FAIL

#define ASSERT_INT_ZERO(n)                                                 \
  if (n != 0)                                                                  \
  return LOCO_FAIL

#define ASSERT_PTR_NOT_NULL(p1)                                                \
  if (p1 == NULL)                                                              \
  return LOCO_FAIL

#define ASSERT_PTR_NULL(p1)                                                    \
  if (p1 != NULL)                                                              \
  return LOCO_FAIL

#define ADD_TEST(func) add_test(func, #func, strlen(#func), suite)

#define CREATE_SUITE(name)                                                     \
  struct test_suite *suite = create_test_suite(name, strlen(name))

#define RUN_TESTS() run_tests(suite)

#define END_TEST() return LOCO_SUCCESS
#endif
