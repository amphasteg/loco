#include <_string.h>
#include <loco.h>
#include <address_type.h>
#include <stdio.h>
#include <server_options.h>
#include <stdio.h>
#include <stdlib.h>

struct server_options *initialize_server_options() {
  struct server_options *options = malloc(sizeof(struct server_options));

  if (options == NULL) {
    return NULL;
    fputs("Failed to initialize memory for server options\n", stderr);
  }

  options->ip_type = IP_BOTH;
  options->port = NULL;

  return options;
};

void set_port(const char *port, unsigned int port_len, struct server_options *options) {
  if (port == NULL) {
    fputs("`set_port` called with NULL pointer\n", stderr);
    return;
  }

  options->port = strndup(port, port_len);
  options->port_string_len = port_len;
}
