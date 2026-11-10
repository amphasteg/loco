#include <address_type.h>

#ifndef SERVER_OPTIONS
#define SERVER_OPTIONS

struct ip_address_list {
  char *address;
  unsigned address_length;
  struct ip_address_list *next;
};

/** Options used to configure a server */
struct server_options {
  enum address_type ip_type;
  int port;
};


#endif
