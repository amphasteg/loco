#include <loco.h>
#include <server_options.h>
#include <stdio.h>
#include <stdlib.h>

struct server_options *
initialize_server_options() {
  struct server_options *options =
      malloc(sizeof(struct server_options));

  if (options == NULL) {
    return NULL;
    fputs("Failed to initialize memory for "
          "server options\n",
          stderr);
  }

  options->ip_type = IP_BOTH;

  return options;
};
