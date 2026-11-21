#include <addrinfo.h>
#include <address_type.h>
#include <stdint.h>
#include <stdio.h>
#include <loco_response_codes.h>

#ifdef _WIN32
#include <WS2tcpip.h>
#include <Winsock2.h>
#else
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#endif


int get_address_info(struct addrinfo **info,
                     struct addrinfo *hints) {
  int return_value;
  char *node = HOST;
  char *service = SERVICE;

  printf("Attemtping to get address information "
         "using the following: "
         "\nHOST:%s\nPORT:%s\n\n",
         node, service);

  if ((return_value = getaddrinfo(
           node, service, hints, info)) != 0) {
    fprintf(
        stderr,
        "Error getting address information: %s\n",
        gai_strerror(return_value));
  }

  return return_value;
}

int set_hints(struct addrinfo *hints,
               enum address_type type) {
  if (hints == NULL) {
    fputs("Cannot set null hints.\n", stderr);
    return PROVIDED_NULL;
  }

  // This is very important on Windows otherwise
  // it blows everything up
  memset(hints, 0, sizeof(struct addrinfo));

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

  return LOCO_SUCCESS;
}
