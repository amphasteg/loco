#include <address_type.h>
#include <stdint.h>
#include <stdio.h>

#ifdef _WIN32
#include <WS2tcpip.h>
#include <Winsock2.h>
#else
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#endif

#ifdef LOCO_RELEASE
#define HOST NULL
#define SERVICE "80"
#else
#define HOST "localhost"
#define SERVICE "8080"
#endif

int get_address_info(struct addrinfo *info,
                     struct addrinfo *hints,
                     const int port) {
  int return_value;
  char service[6];

  if (port == 0 || port > UINT16_MAX)
    strncpy(service, SERVICE, 4);
  else
    snprintf(service, 6, "%d", port);

  service[5] = '\0';

  if ((return_value = getaddrinfo(
           HOST, service, hints, &info)) != 0) {
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
  hints->ai_protocol = IPPROTO_TCP;

  return;
}
