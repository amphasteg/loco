// TODO Write docs for this
#include <loco_response_codes.h>

struct server;
struct server_options;

int create_server(struct server_options *, struct server *server);

void server_listen(struct server *);

struct server_options *initialize_server_options();

void server_listen(struct server *server);
