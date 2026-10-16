#include "../src/hostname.c"
#include "tests.h"

int main(void) {
  set_mock_malloc_errno(ENOMEM);
  void *test = malloc(1);
  if (test == NULL)
    printf("Test worked!");
}

