#include "loco.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <WS2tcpip.h>
#include <Winsock2.h>
#else
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

// Flags to determine if a socket of either IPv4
// or IPv6 needs to be bound and collected
struct binding_flags {
  unsigned ipv4_uneeded : 1;
  unsigned ipv6_uneeded : 1;
  unsigned target_ips : 1;
};

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

int address_allowed(struct ip_address *allowed, struct sockaddr *sockaddr, unsigned flag) {
  if (!flag)
    return 1;

  switch (sockaddr->sa_family) {
    case AF_INET:
      char str[INET_ADDRSTRLEN];
      break;
    case AF_INET6:
      char str[INET6_ADDRSTRLEN];
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
  get_address_info(&address_info, &hints,
                   options->port);

  return server;
}

struct server_options
initialize_server_options() {
  struct server_options options;

  memset(&options, 0, sizeof(options));

  return options;
}
