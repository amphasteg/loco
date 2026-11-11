#ifndef LOCO_SOCKET
#ifdef WIN32
#include <WinSock2.h>
#else
#include <netdb.h>
#endif

#define LOCO_SOCKET

struct listening_sock_list;

int add_listening_sockets(struct listening_sock_list *socket_list,
                          struct addrinfo *address_info);

struct listening_sock_list *initialize_socket_list(void);

void listen_on_sockets(struct listening_sock_list *list);

#endif
