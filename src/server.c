#include <addrinfo.h>
#include <hostname.h>
#include <loco.h>
#include <loco_socket.h>
#include <server.h>
#include <server_options.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  set_hints(&hints, options->ip_type);
  get_address_info(&address_info, &hints,
                   options->port);
  server.socket_list = initialize_socket_list();
  add_listening_sockets(server.socket_list,
                        &address_info);

  return server;
}
