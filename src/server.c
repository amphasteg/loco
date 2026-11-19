#include "wsa.h"
#include <addrinfo.h>
#include <hostname.h>
#include <loco.h>
#include <loco_socket.h>
#include <server.h>
#include <server_options.h>
#include <stdio.h>
#include <stdlib.h>

int failed_allocating(const char *error_msg) {
  if (error_msg != NULL)
    fprintf(stderr,
            "Failure allocating memory for %s.",
            error_msg);

  fprintf(stderr,
          "Cannot create server "
          "object.\n Error code: %d\n",
          errno);
  perror(NULL);
  return SERVER_ALLOC_ERROR;
}

int create_server(struct server_options *options,
                  struct server *server) {
  struct addrinfo *hints, *address_info;

  if (initialize_wsa() != WSA_SUCCESS) {
    return WSA_ERROR;
  }

  hints = calloc(1, sizeof(struct addrinfo));

  if (hints == NULL)
    return failed_allocating("hints");

  address_info =
      calloc(1, sizeof(struct addrinfo));

  if (address_info == NULL)
    return failed_allocating("address info");

  server = calloc(1, sizeof(struct server));

  if (server == NULL)
    return failed_allocating("server");

  server->hostname = get_hostname();

  set_hints(hints, options->ip_type);
  get_address_info(&address_info, hints);
  server->socket_list = initialize_socket_list();
  add_listening_sockets(server->socket_list,
                        address_info);

  freeaddrinfo(hints);
  freeaddrinfo(address_info);

  return SERVER_CREATE_SUCCESS;
}

void server_listen(struct server *server) {}
