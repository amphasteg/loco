#include "../include/loco.h"
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
