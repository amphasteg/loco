#ifdef _WIN32
#include <Winsock2.h>
#else
#include <unistd.h>
#endif
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <testing_mocks.h>

int mock_malloc_errno = 0;
char *gethostname_string = NULL;
int gethostname_errno = 0;

void *mock_malloc(size_t ptr_size) {
  if (mock_malloc_errno == 0)
    return malloc(ptr_size);

  errno = mock_malloc_errno;
  return NULL;
}

int mock_gethostname(char *name, int name_len) {
  if (gethostname_errno != 0) {
    name = NULL;

#ifdef WIN32
    WSASetLastError(gethostname_errno);
#endif

    return gethostname_errno;
  }

  if (gethostname_string == NULL) {

#ifdef WIN32
    WSADATA wsadata;
    int status =
        WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (status != 0) {
      printf("Failed to start WSA. Error: %d\n",
             status);
      return status;
    }
#endif

    return gethostname(name, name_len);
  }

  int hostname_len = strlen(gethostname_string);
  int len;

  if (hostname_len > name_len) {
    strncpy(name, gethostname_string, name_len);
    name[name_len] = '\0';
  } else {
    strncpy(name, gethostname_string,
            hostname_len);
    name[hostname_len] = '\0';
  }

  return 0;
}

void set_mock_malloc_errno(int error) {
  mock_malloc_errno = error;
}

void set_mock_gethostname_string(
    const char *host_name, const int name_len) {

  if (host_name == NULL) {
    return;
  }

  int size = name_len + 1;
  gethostname_string = malloc(size);
  if (host_name == NULL) {
    fputs("Failed to allocate mock hostname\n",
          stderr);
    return;
  }

  strncpy(gethostname_string, host_name, size);
  gethostname_string[name_len] = '\0';
}

void set_mock_gethostname_errno(int err) {
  gethostname_errno = err;
}

void set_gethostname_mocks(
    int error_num, char *mock_hostname,
    int mock_hostname_len) {
  set_mock_gethostname_string(mock_hostname,
                              mock_hostname_len);
  set_mock_gethostname_errno(error_num);
}
