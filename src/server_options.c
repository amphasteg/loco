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

enum loco_response_code
set_ip_type(struct server_options *options,
            enum address_type ip_type) {
  if (options == NULL) {
    fputs("Passed null sever options when "
          "setting IP type.\n",
          stderr);
    return PROVIDED_NULL;
  }

  if (ip_type > IPV6) {
    fputs("An invalid options for IP type was "
          "passed. Setting default of IP_BOTH.\n",
          stderr);
    options->ip_type = IP_BOTH;
    return ENUM_OUT_OF_RANGE;
  }

  options->ip_type = ip_type;

  return LOCO_SUCCESS;
}
