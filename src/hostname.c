#include <stdio.h>
#ifdef _WIN32
#include <Winsock2.h>
#else
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#endif
#include <hostname.h>

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
    return index +
           1; // Return the size of the string
              // including null char
  else
    return 0;
}

struct string *get_hostname() {
  int size = 100;
  struct string *hostname_str =
      malloc(sizeof(struct string));
  char *hostname = malloc(sizeof(char) * size);
  int hostname_size = 0;

  if (hostname == NULL) {
    fputs("Failed to initialize enough memory for "
          "hostname\n",
          stderr);
    errno = ENOMEM;
    return NULL;
  }

  if (hostname_str == NULL) {
    fputs("Failed to allocated enough memory for "
          "loco string\n",
          stderr);
    errno = ENOMEM;
    return NULL;
  }


  while (hostname_size == 0 && hostname != NULL) {
    int error_code = gethostname(hostname, size);
    if (error_code != 0) {

#ifdef WIN32
      error_code = WSAGetLastError();
#endif

      printf("`gethostname` returned error. "
             "Error: %d\n",
             errno);

      return NULL;
    }

    hostname_size =
        verify_hostname(hostname, size);

    size += 100;

    // This will set hostname to null if fail,
    // this will be caught later if the case
    hostname =
        realloc(hostname, sizeof(char) * size);
  }

  if (hostname == NULL || hostname_size == 0) {
    errno = ENOMEM;
    return NULL;
  }

  hostname = realloc(hostname, sizeof(char) *
                                   hostname_size);

  hostname_str->string = hostname;
  hostname_str->string_size = hostname_size;

  return hostname_str;
}
