#include "loco_response_codes.h"
#include <wsa.h>

#ifdef WIN32

#include <WS2tcpip.h>
#include <Winsock2.h>
#include <stdio.h>

void get_message(DWORD error, char **message) {
  DWORD flags;

  flags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
          FORMAT_MESSAGE_FROM_SYSTEM |
          FORMAT_MESSAGE_IGNORE_INSERTS;

  DWORD format_error = FormatMessage(
      flags, NULL, error, LANG_SYSTEM_DEFAULT,
      (LPSTR)message, 0, NULL);
}

enum loco_response_code initialize_wsa() {
  WSADATA wsaData;
  int wsa_status =
      WSAStartup(MAKEWORD(2, 2), &wsaData);

  if (wsa_status != 0) {
    char *message;
    get_message(wsa_status, &message);
    fprintf(stderr,
            "WSAStartup failed with error code: "
            "%d.\n Error message: %s\n",
            wsa_status, message);
    LocalFree(message);
    WSACleanup();
    return WSA_ERROR;
  }

  if (LOBYTE(wsaData.wVersion) < 2 ||
      HIBYTE(wsaData.wVersion) < 2) {
    fputs("Version 2.2 of WinSock is not "
          "available.\n",
          stderr);
    return WSA_UNAVAILABLE;
  }

  return LOCO_SUCCESS;
}

void wsa_cleanup() { WSACleanup(); }

#else

// On non-Windows platforms, these functions do
// not matter.
void wsa_cleanup() { return; }
enum loco_response_code initialize_wsa() { return LOCO_SUCCESS; }

#endif
