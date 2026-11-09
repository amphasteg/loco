#include <loco_string.h>
#include <address_type.h>
#include <stddef.h>

struct server {
  /* Address type used for the server and every listening socket.
   * For instance, if the server has a socket listening on IPV4 and IPV6, this
   * value will be BOTH. If a server has only IPV4 listening sockets, then it
   * will be set to IPV4
   */
  enum address_type listening_type;
  struct string *hostname;
  struct listening_sock_list *socket_list;
};
