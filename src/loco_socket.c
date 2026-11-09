#include <address_type.h>
#include <arpa/inet.h>
#include <errno.h>
#include <loco.h>
#include <loco_socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/socket.h>
#ifdef _WIN32
#include <WS2tcpip.h>
#include <Winsock2.h>
#else
#include <string.h>
#endif

union listening_sock {
  struct sockaddr_in ipv4;
  struct sockaddr_in6 ipv6;
};

struct listening_sock_item {
  union listening_sock *socket;
  enum address_type ip_type;
};

struct listening_sock_list {
  struct listening_sock_item *socket_item;
  unsigned int list_size;
};

int increment_list_size(
    struct listening_sock_list *socket_list) {
  unsigned new_size = socket_list->list_size + 1;
  struct listening_sock_item *new_socket_item;

  new_socket_item =
      realloc(socket_list->socket_item,
              sizeof(struct listening_sock_item) *
                  new_size);

  if (new_socket_item == NULL) {
    fputs("Failed to resize socket list; "
          "memory error\n",
          stderr);
    return -1;
  }

  free(socket_list->socket_item);
  socket_list->socket_item = new_socket_item;
  socket_list->list_size = new_size;

  return new_size;
}

int append(
    struct listening_sock_list *socket_list,
    struct addrinfo *address_info) {
  int new_size = increment_list_size(socket_list);

  if (new_size == -1)
    return new_size;

  if (address_info == NULL) {
    fputs("Cannot append null addrinfo\n",
          stderr);
    return 1;
  }

  struct listening_sock_item *new_item =
      socket_list->socket_item + new_size - 1;

  new_item->socket =
      malloc(sizeof(union listening_sock));

  if (address_info->ai_family == AF_INET) {
    new_item->socket->ipv4 =
        *(struct sockaddr_in *)
             address_info->ai_addr;
    new_item->ip_type = IPV4;
  } else {
    new_item->socket->ipv6 =
        *(struct sockaddr_in6 *)
             address_info->ai_addr;
    new_item->ip_type = IPV6;
  }

  return 0;
}

int add_listening_sockets(
    struct listening_sock_list *socket_list,
    struct addrinfo *address_info) {
  int result;
  for (struct addrinfo *p = address_info;
       p != NULL; p = p->ai_next) {
    result = append(socket_list, p);

    if (result != 0)
      break;
  }

  return result;
}
