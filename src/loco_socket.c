#include <address_type.h>
#include <loco.h>
#include <loco_socket.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
#include <WS2tcpip.h>
#include <Winsock2.h>
#else
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/socket.h>
#endif

struct listening_sock {
  enum address_type ip_type;
  unsigned long long sock_descriptor;
  char *ip_address;
};

struct listening_sock_item {
  struct listening_sock *socket;
};

struct listening_sock_list {
  struct listening_sock_item *socket_item;
  unsigned int list_size;
};

int increment_list_size(
    struct listening_sock_list *socket_list) {
  if (socket_list == NULL) {
    fputs("Cannot increment on null list\n", stderr);
    return -1;
  }

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
  if (socket_list == NULL) {
    fputs("Cannot append to null list\n", stderr);
    return 1;
  }

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
      malloc(sizeof(struct listening_sock));

  if (address_info->ai_family == AF_INET) {
    new_item->socket->ip_address =
        malloc(sizeof(char) * INET_ADDRSTRLEN);
    inet_ntop(AF_INET, address_info->ai_addr,
              new_item->socket->ip_address,
              INET_ADDRSTRLEN);
    new_item->socket->ip_type = IPV4;
    new_item->socket->sock_descriptor =
        socket(address_info->ai_family,
               address_info->ai_socktype,
               address_info->ai_protocol);
  } else {
    new_item->socket->ip_address =
        malloc(sizeof(char) * INET6_ADDRSTRLEN);
    inet_ntop(AF_INET6, address_info->ai_addr,
              new_item->socket->ip_address,
              INET6_ADDRSTRLEN);
    new_item->socket->ip_type = IPV6;
    new_item->socket->sock_descriptor =
        socket(address_info->ai_family,
               address_info->ai_socktype,
               address_info->ai_protocol);
  }

  return 0;
}

int add_listening_sockets(
    struct listening_sock_list *socket_list,
    struct addrinfo *address_info) {
  if (socket_list == NULL) {
    fputs("Cannot add listening sockets to null socket list.\n", stderr);
    return 1;
  }

  int result;
  for (struct addrinfo *p = address_info;
       p != NULL; p = p->ai_next) {
    result = append(socket_list, p);

    if (result != 0)
      break;
  }

  return result;
}

struct listening_sock_list *intialize_socket_list() {
  struct listening_sock_list *socket_list = malloc(sizeof(struct listening_sock_list));

  socket_list->socket_item = NULL;
  socket_list->list_size = 0;

  return socket_list;
}
