#ifdef _WIN32
#include <Winsock2.h>
#endif
#include <stdlib.h>
#include "internal.h"
int verify_hostname(const char *hostname,
                    const int len) {
  int index;
  for (int index = 0; index < len; index++) {
    if (hostname[index] == '\0')
      break;
  }

  /*The POSIX standard does not specify if the
   * last character of a truncated hostname ends
   * with '\0', so if the index is set to the last
   * available slot of the char, we cannot be
   * certain if it was truncated, hence the need
   * to verify that the index is not greather than
   * the second to last index
   */
  if (index < len - 1)
    return 0;
  else
    return 1;
}

int get_hostname(char **hostname) {
  int size = 100;

  if (*hostname != NULL) {
    free(*hostname);
    *hostname = malloc(sizeof(char) * size);
  }

  while (*hostname != NULL)
  {
    int error_code;
    if ((error_code = gethostname(*hostname, size)) !=
        0) {
      return error_code;
    }

    if (verify_hostname(*hostname, size) == 0)
      break;

    size += 100;
    realloc(*hostname, sizeof(char) * size);
  }

  if (*hostname == NULL)
    return 2;

  return 0;
}
