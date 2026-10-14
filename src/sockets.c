#include "../include/loco.h"
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/errno.h>
#ifdef _WIN32
#include <WS2tcpip.h>
#include <Winsock2.h>
#else
#include <netdb.h>
#include <string.h>
#endif

// Flags to determine if a socket of either IPv4
// or IPv6 needs to be bound and collected
struct binding_flags {
  unsigned ipv4_uneeded : 1;
  unsigned ipv6_uneeded : 1;
  unsigned target_ips : 1;
};

void set_flags(struct binding_flags *flags,
               struct server_options *options) {
  memset(flags, 0, sizeof(*flags));

  switch (options->ip_type) {
  case IPV4:
    flags->ipv6_uneeded = 1;
    break;
  case IPV6:
    flags->ipv4_uneeded = 1;
    break;
  default:
    break;
  }

  if (options->ip_addresses != NULL)
    flags->target_ips = 1;

  return;
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

void get_address_info(struct addrinfo *info,
                      struct addrinfo *hints,
                      const char *port) {
  int return_value;

  if ((return_value = getaddrinfo(
           NULL, port, hints, &info)) != 0) {
    fprintf(
        stderr,
        "Error getting address information: %s\n",
        gai_strerror(return_value));
    exit(1);
  }

  return;
}


int address_allowed(struct ip_address *allowed, struct sockaddr *sockaddr) {
  char str[INET6_ADDRSTRLEN];

  switch (sockaddr->sa_family) {
    case AF_INET:
      inet_ntop(AF_INET, (struct sockaddr_in *) sockaddr, str, INET_ADDRSTRLEN);
      break;
    case AF_INET6:
      inet_ntop(AF_INET6, (struct sockaddr_in6 *) sockaddr, str, INET6_ADDRSTRLEN);
      break;
    default:
      errno = EPROTOTYPE; 
      return -1;
  }
}

void add_listening_socket(
    struct server *server, struct addrinfo *info,
    struct server_options *options) {}

void bind_sockets(
    struct server *server,
    struct addrinfo *address_info,
    struct server_options *options) {

  struct binding_flags *flags;
  set_flags(flags, options);

  struct listening_socket listening_sock;
  for (struct addrinfo *p = address_info;
       p != NULL; p = p->ai_next) {
    if (flags->ipv4_uneeded && flags->ipv6_uneeded)
      break;
    
    switch (p->ai_family) {
      case AF_INET:
        if (flags->ipv4_uneeded)
          continue;
        if (flags->target_ips) {
          char addr_str[INET_ADDRSTRLEN];
          struct sockaddr_in *addr_in = (struct sockaddr_in *)p;
          inet_ntop(AF_INET, &(addr_in->sin_addr), addr_str, INET_ADDRSTRLEN);
        }


  }

}
