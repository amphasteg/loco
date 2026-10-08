#include "loco.h"
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <WS2tcpip.h>
#include <Winsock2.h>
#else
#endif

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
    return -1;
}

char *get_hostname(void) {
  char *hostname;
  for (int i = 100;; i += 100) {
    int error_code;
    if ((error_code = gethostname(hostname, i)) !=
        0) {
      fprintf(stderr,
              "Error retrieiving hostname. Error "
              "code %d\n",
              error_code);
      exit(errno);
    }

    if (verify_hostname(hostname, i) == 0)
      break;
  }
  return hostname;
}

void set_hints(struct addrinfo *hints, enum address_type type) {
  if (type == IPV4)
    hints->ai_family = AF_INET;
  else if (type == IPV6)
    hints->ai_family = AF_INET6;
  else
   hints->ai_family = AF_UNSPEC;

  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
}

void get_address_info(struct addrinfo *info, struct addrinfo *hints, const char *port) {
  int return_value;

  if ((return_value = getaddrinfo(NULL, port, hints, &info)) != 0)
  {
    fprintf(stderr, "Error getting address information: %s\n", gai_strerror(return_value));
    exit(1);
  }
}

struct server
create_server(struct server_options *options) {
  struct server server;
  struct addrinfo hints, address_info;

#ifdef _WIN32
  WSADATA wsData;
  if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
    perror("Failed to initialize Winsock\n");
    exit(1);
  }
#endif

  memset(&server, 0, sizeof(server));
  memset(&hints, 0, sizeof(hints));

  server.hostname = get_hostname();
  server.hostname_len = strlen(server.hostname);

  set_hints(&hints, options->ip_type);
  get_address_info(&address_info, &hints, options->port);
  

  return server;
}

struct server_options
initialize_server_options() {
  struct server_options options;

  memset(&options, 0, sizeof(options));

  return options;
}
