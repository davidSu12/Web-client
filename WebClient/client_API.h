//
// Created by sam_s on 10/06/2025.
//

#ifndef WEBSERVER_CLIENT_API_H
#define WEBSERVER_CLIENT_API_H

#include "header.h"

#define MAX_LEN 512
#define TIMEOUT 5.0



SOCKET connect_to_host(char *hostname, char *port);
void send_request_GET(SOCKET s, char *hostname, char *port, char *path);
void send_request_HEAD(SOCKET s, char *hostname, char *port, char *path);

#endif //WEBSERVER_CLIENT_API_H
