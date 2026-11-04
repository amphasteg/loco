#include <stdio.h>
#ifdef _WIN32
#include <Winsock2.h>
#else
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#endif
#include <loco_internal.h>

#undef mock_malloc
/**
 * Verifies hostname was not truncated when
 * returning from the 'gethostname' call. If
 * truncated, the program returns 0. If not, it
 * will return the length of the string
 *
 * The POSIX standard does not specify if the
 * last character of a truncated hostname ends
 * with '\0', so if the last char is set to be
 * '\0', we cannot be certain if it was truncated,
 * hence the need to verify that the hostname.
 *
 * @param hostname Null terminated string
 * @param size Size of the container that holds
 * the string, including the null terminator '\0'
 * @return The size of the hostname
 */
int verify_hostname(const char *hostname,
                    const int size) {
  int index = 0;

  while (index < size && hostname[index] != '\0')
    index++; 

  // If index fits within the container, string
  // was not truncated.
  if (index < size - 1)
    return index + 1; //Return the size of the string including null char
  else
    return 0;
}

char *get_hostname() {
  int size = 100;
  char *hostname = malloc(sizeof(char) * size);

  if (hostname == NULL) {
    return NULL;
  }

  do {
    int error_code = gethostname(hostname, size);
    if (error_code != 0) {
#ifdef WIN32
      int error = WSAGetLastError();
      printf("`gethostname` returned error. "
             "errno: %d\n",
             error);
#else
      printf("`gethostname` returned error. "
             "errno: %d\n",
             errno);
#endif
      return NULL;
    }

    int hostname_len =
        verify_hostname(hostname, size);

    // Hostname was validated and has a length.
    // Reallocate to correct size and break.
    if (hostname_len > 0) {
      hostname = realloc(
          hostname, sizeof(char) * hostname_len);
      break;
    }

    size += 100;
    hostname =
        realloc(hostname, sizeof(char) * size);
  } while (hostname != NULL);

  if (hostname == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  return hostname;
}
