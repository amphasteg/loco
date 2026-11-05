#ifdef _WIN32
#include <WS2tcpip.h>
#include <Winsock2.h>
#else
#include <netdb.h>
#endif
#include <address_type.h>

void set_hints(struct addrinfo *hints,
               enum address_type type);

int get_address_info(struct addrinfo *info,
                     struct addrinfo *hints,
                     const char *port);
