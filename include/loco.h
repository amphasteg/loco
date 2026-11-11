struct server;
struct server_options;

struct server create_server(struct server_options *);

void server_listen(struct server *);

struct server_options *initialize_server_options();

void set_port(const int port, struct server_options *options);

void server_listen(struct server *server);
