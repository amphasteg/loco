target_sources(loco
  PRIVATE
  FILE_SET private_headers
  TYPE HEADERS
  FILES
    addrinfo.h
    hostname.h
    loco_socket.h
    server.h
    server_options.h
    loco_string.h
)

target_sources(loco
  PRIVATE
    addrinfo.c
    hostname.c
    loco_socket.c
    server.c
    server_options.c
)
