#ifndef _WIN32
#include <stddef.h>
#endif

/**
 * IP version
 */
enum address_type { IP_BOTH, IPV4, IPV6 };

struct ip_address {
  char *address;
  size_t address_len;
};

/** Options used to configure a server */
struct server_options {
  enum address_type ip_type;
  size_t port_string_len;
  char *port;
  //If the user wishes to specify a list of IP addresses to use in this program, they may do so in this list.
  struct ip_address *ip_addresses; 
};

/** Contains the IP type, the adress, socket that is bound, and the next socket
 * in the linked list */
struct listening_socket {
  /** The IP version used for this specific socket */
  enum address_type listening_type;
  /** File descripter for listening socket */
  int socket;
  /** Length of IP address for given listening socket */
  size_t address_len;
  /** IP address for bound socket */
  char *address;
  /** Next listening socket in linked list */
  struct listening_socket *next;
};

struct server {
  /* Address type used for the server and every listening socket.
   * For instance, if the server has a socket listening on IPV4 and IPV6, this
   * value will be BOTH. If a server has only IPV4 listening sockets, then it
   * will be set to IPV4
   */
  enum address_type listening_type;
  size_t listening_socket_len;
  struct listening_socket *listening_sockets;
  size_t hostname_len;
  char *hostname;
};

struct server create_server(struct server_options *);

struct server_options initialize_server_options(void);

void server_listen(struct server *);
