//
// Created by sam_s on 10/06/2025.
//

#ifndef WEBSERVER_AUXFUNC_H
#define WEBSERVER_AUXFUNC_H
#include "header.h"



int parse_url(char *url,
               char **hostname,
               char **port,
               char **path
               );

SOCKET connect_to_host(char *hostname, char *port);
void send_request_GET(SOCKET s, char *hostname, char *port, char *path);


#endif //WEBSERVER_AUXFUNC_H
