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

struct loco_socket {
  enum address_type ip_type;
  int sock_protocol;
  int socktype;
  socklen_t sock_address_len;
  unsigned long long sock_descriptor;
  char ip_address[INET6_ADDRSTRLEN];
  struct sockaddr *socket_address;
};

struct listening_sock_list {
  struct loco_socket *socket_item;
  unsigned int list_size;
};

/** Increases the size of the list of socket_items
 * (by increasing the block pointed to at the
 * first list item).
 * @returns The new size of the list, or -1 if an
 * error occured.
 */
int increment_list_size(
    struct listening_sock_list *socket_list) {
  if (socket_list == NULL) {
    fputs("Cannot increment on null list\n",
          stderr);
    return -1;
  }

  unsigned new_size = socket_list->list_size + 1;
  struct loco_socket *new_socket_item;

  new_socket_item = realloc(
      socket_list->socket_item,
      sizeof(struct loco_socket) * new_size);

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

int append_memory_failure() {
  fputs("Failed to assign memory to append "
        "socket\n",
        stderr);
  return 1;
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

  struct loco_socket *new_item =
      socket_list->socket_item + new_size - 1;

  new_item = malloc(sizeof(struct loco_socket));

  if (new_item == NULL)
    return append_memory_failure();

  new_item->socket_address =
      malloc(sizeof(struct addrinfo));

  if (new_item->socket_address == NULL)
    return append_memory_failure();

  new_item->sock_descriptor =
      socket(address_info->ai_family,
             address_info->ai_socktype,
             address_info->ai_protocol);

  memcpy(new_item->socket_address,
         address_info->ai_addr,
         sizeof(struct sockaddr));

  new_item->sock_address_len =
      address_info->ai_addrlen;
  new_item->sock_protocol =
      address_info->ai_protocol;
  new_item->socktype = address_info->ai_socktype;
  inet_ntop(address_info->ai_family,
            address_info->ai_addr,
            new_item->ip_address,
            INET6_ADDRSTRLEN);

  if (address_info->ai_family == AF_INET)
    new_item->ip_type = IPV4;
  else
    new_item->ip_type = IPV6;

  return 0;
}

int add_listening_sockets(
    struct listening_sock_list *socket_list,
    struct addrinfo *address_info) {
  if (socket_list == NULL) {
    fputs("Cannot add listening sockets to null "
          "socket list.\n",
          stderr);
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

struct listening_sock_list *
intialize_socket_list() {
  struct listening_sock_list *socket_list =
      malloc(sizeof(struct listening_sock_list));

  socket_list->socket_item = NULL;
  socket_list->list_size = 0;

  return socket_list;
}

int verify_socket_fields(
    struct loco_socket *socket) {
  if (socket->sock_descriptor < 1 ||
      socket->socket_address == NULL ||
      socket->sock_address_len < 1)
    return 1;

  return 0;
}

void listen_on_sockets(
    struct listening_sock_list *list) {
  if (list == NULL) {
    fputs("Socket list is null. Not listening on "
          "any sockets.\n",
          stderr);
    return;
  }

  for (int i = 0; i < list->list_size; i++) {
    struct loco_socket *list_item =
        (list->socket_item) + i;

    if (list_item == NULL) {
      fprintf(stderr,
              "Socket list item %d is null.", i);
      continue;
    }

    if (verify_socket_fields(list_item) != 0) {
      fprintf(stderr,
              "Failed to verify neccessary "
              "fields were valid to bind to "
              "socket for IP address %s\n.",
              list_item->ip_address);
      continue;
    }

    int socket_result =
        bind(list_item->sock_descriptor,
             list_item->socket_address,
             list_item->sock_address_len);

    if (socket_result == -1)
      fprintf(stderr,
              "Failed to bind to socket at IP "
              "address %s\n.",
              list_item->ip_address);
    else
      printf("Successfully bound to socket at IP "
             "address %s\n.",
             list_item->ip_address);
  }
}
