#include <server_options.h>

struct server;

struct server *create_server(struct server_options *);

struct server_options initialize_server_options(void);

void server_listen(struct server *);
