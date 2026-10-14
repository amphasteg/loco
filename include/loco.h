#ifndef _WIN32
#include <stddef.h>
#endif

struct server;

struct server_options;

struct server create_server(struct server_options *);

struct server_options initialize_server_options(void);

void server_listen(struct server *);
