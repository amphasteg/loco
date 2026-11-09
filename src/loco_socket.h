#ifndef LOCO_SOCKET
#include <netdb.h>

#define LOCO_SOCKET

struct listening_sock_list;

int add_listening_sockets(struct listening_sock_list *socket_list,
                          struct addrinfo *address_info);

#endif
