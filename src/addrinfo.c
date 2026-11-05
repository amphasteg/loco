#include <address_type.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <WS2tcpip.h>
#include <Winsock2.h>
#else
#include <netdb.h>
#endif

#ifdef LOCO_RELEASE
#define HOST NULL
#else
#define HOST "localhost"
#endif

int get_address_info(struct addrinfo *info,
                     struct addrinfo *hints,
                     const char *port) {
  int return_value;

  if ((return_value = getaddrinfo(
           HOST, port, hints, &info)) != 0) {
    fprintf(
        stderr,
        "Error getting address information: %s\n",
        gai_strerror(return_value));
  }

  return return_value;
}

void set_hints(struct addrinfo *hints,
               enum address_type type) {
  switch (type) {
  case IPV4:
    hints->ai_family = AF_INET;
    break;
  case IPV6:
    hints->ai_family = AF_INET6;
    break;
  default:
    hints->ai_family = AF_UNSPEC;
    break;
  }

  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;

  return;
}
