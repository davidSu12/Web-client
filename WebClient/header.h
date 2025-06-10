//
// Created by sam_s on 10/06/2025.
//

#ifndef WEBSERVER_HEADER_H
#define WEBSERVER_HEADER_H

#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#define ISVALIDSOCKET(S) ((S) != INVALID_SOCKET)
#define CLOSESOCKET(S) closesocket(S)
#define GETSOCKETERRNO() (WSAGetLastError())
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#define SOCKET int
#define ISVALIDSOCKET(S) ((S) >= 0)
#define CLOSESOCKET(S) close(S)
#define GETSOCKETERRNO() (errno)

#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

#endif


