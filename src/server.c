#include <addrinfo.h>
#include <hostname.h>
#include <loco.h>
#include <loco_socket.h>
#include <server.h>
#include <server_options.h>
#include <stdio.h>
#include <stdlib.h>

struct server
*create_server(struct server_options *options) {
  struct server *server;
  struct addrinfo *hints, *address_info;

#ifdef _WIN32
  WSADATA wsData;
  if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
    perror("Failed to initialize Winsock\n");
    exit(1);
  }
#endif

  hints = calloc(1, sizeof(struct addrinfo));

  if (hints == NULL) {
    fputs("Failed to allocate memory for hints.\n", stderr);
    return NULL;
  }

  address_info = calloc(1, sizeof(struct addrinfo));

  if (address_info == NULL) {
    fputs("Failed to allocate memory for address info.\n", stderr);
    return NULL;
  }

  server = calloc(1, sizeof(struct server));

  if (server == NULL) {
    fputs("Failed to allocate memory for server.\n", stderr);
    return NULL;
  }

  server->hostname = get_hostname();

  set_hints(hints, options->ip_type);
  get_address_info(address_info, hints,
                   options->port);
  server->socket_list = initialize_socket_list();
  add_listening_sockets(server->socket_list,
                        address_info);

  freeaddrinfo(hints);
  freeaddrinfo(address_info);

  return server;
}

void server_listen(struct server *server) {
}
