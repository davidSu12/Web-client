//
// Created by sam_s on 10/06/2025.
//

#ifndef WEBSERVER_AUXFUNC_H
#define WEBSERVER_AUXFUNC_H

#include <string.h>

int parse_url(char *url,
               char **hostname,
               char **port,
               char **path
               );




#endif //WEBSERVER_AUXFUNC_H
