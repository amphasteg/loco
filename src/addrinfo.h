#ifndef LOCO_ADDRINFO
#define LOCO_ADDRINFO

#ifdef LOCO_RELEASE
#define HOST NULL
#define SERVICE "80"
#else
#define HOST "localhost"
#define SERVICE "8080"
#endif

#include <stdint.h>
#ifdef _WIN32
#include <WS2tcpip.h>
#include <Winsock2.h>
#else
#include <netdb.h>
#endif
#include <address_type.h>

int set_hints(struct addrinfo *hints, enum address_type type);

int get_address_info(struct addrinfo **info, struct addrinfo *hints);

#endif
