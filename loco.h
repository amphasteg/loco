/**
 * IP version
 */
enum address_type { IP_BOTH, IPV4, IPV6 };

/** Options used to configure a server */
struct server_options {
  enum address_type ip_type;
  size_t port_string_len;
  const char *port;
};

/** Contains the IP type, the adress, and socket that is bound */
struct listening_socket {
  /** The IP version used for this specific socket */
  enum address_type listening_type;
  /** Length of IP address for given listening socket */
  size_t address_len;
  /** File descripter for listening socket */
  unsigned socket;
  /** IP address for bound socket */
  char *address; 
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
