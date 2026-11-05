/**
 * IP version
 */
enum address_type { IP_BOTH, IPV4, IPV6 };

struct ip_address_list {
  char *address;
  unsigned address_length;
  struct ip_address_list *next;
};

/** Options used to configure a server */
struct server_options {
  enum address_type ip_type;
  unsigned port_string_len;
  char *port;
  //If the user wishes to specify a list of IP addresses to use in this program, they may do so in this list.
  struct ip_address *desired_addresses; 
};

/** Adds an IP address to the linked list
 */
int add_desired_ip(struct ip_address_list *ip_list, const char *address, unsigned address_length);
