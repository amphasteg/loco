// TODO Write docs for this
#include <address_type.h>
#include <loco_response_codes.h>

struct server;
struct server_options;

int create_server(struct server_options *, struct server *server);

void server_listen(struct server *);

struct server_options *initialize_server_options();
enum loco_response_code set_ip_type(struct server_options *options,
                                    enum address_type ip_type);

void server_listen(struct server *server);
