
#ifndef ADDR_H
#ifdef _WIN32
#include <ws2tcpip.h>
#endif
#define ADDR_H 

/*Returns a pointer to the correct struct for IPv4 or IPv6 sockets.
 * @param sa The sock address to return the correct struct for
 * @return A sockaddr_in or sockaddr_in6 for the given socket
 */
void *get_internet_address(struct sockaddr *sa);

#endif
