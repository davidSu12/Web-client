#include "auxfunc.h"





int parse_url(char *url,
               char **hostname,
               char **port,
               char **path){


    char *p;
    p = strstr(url, "://");
    printf("%s\n", url);


    char *protocol;
    if(!p){
        //there is no ptorocol specified, then we assume that is http
        *protocol = 0;
    }else {
        //encontramos el propio protocolo
        protocol = url;
        *p = 0;
        p += 3;
    }



    if(protocol){
        if(strcmp(protocol, "http") != 0){
            fprintf(stderr,
                    "No http specified, aborting operation!");
            return -1;
        }
    }


    //p is pointing to our hostname
    *hostname = p;
    while(*p != ':' && *p != '/' && *p != 0 && ++p);
    /*
     *a port is being specified or we are in the slash already
     */
    if(*p == ':'){
        //a port is being specified
        *p = 0;
        ++p;
        *port = p;
        while(*p != '/' && *p != 0 && ++p);
        *p = 0;
        ++p;
        *path = p;

    }else if(*p == '/'){
        *p = 0;
        ++p;
        *path = p;
        *port = NULL;

    }else{
        //no path is being specified so we asume that the path is equal to /
        *path = NULL;
    }

    return 0;

}
