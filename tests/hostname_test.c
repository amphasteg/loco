#include <sys/errno.h>
#include <tests.h>
#include "hostname.c"

int main(void) {
  set_mock_malloc_errno(ENOMEM);
  void *test = malloc(1);
  if (test == NULL)
    return 0;
  else
    return -1;
}
