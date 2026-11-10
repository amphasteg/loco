#include <loco.h>
#include <stdio.h>
#include <server_options.h>
#include <stdlib.h>

struct server_options *initialize_server_options() {
  struct server_options *options = malloc(sizeof(struct server_options));

  if (options == NULL) {
    return NULL;
    fputs("Failed to initialize memory for server options\n", stderr);
  }

  options->ip_type = IP_BOTH;
  options->port = 0;

  return options;
};

void set_port(const int port, struct server_options *options) {
  options->port = port;
}
