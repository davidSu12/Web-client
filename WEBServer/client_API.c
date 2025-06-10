#include "client_API.h"



/*
 * This procedure just helps to connect to the host
 * input:
 * -hostname: string that aims to the host (ex: google.com)
 * -port: string that aims to the port to connect(ex: http, 80, smtp 25)
 */

SOCKET connect_to_host(char *hostname, char *port){

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *tar;
    if(getaddrinfo(hostname, port, &hints, &tar)){
        fprintf(stderr, "An error has ocurred while resolving host (%d)", WSAGetLastError());
        exit(EXIT_FAILURE);
    }


    SOCKET sock_peer;
    sock_peer = socket(tar -> ai_family,
                       tar -> ai_socktype,
                       tar -> ai_protocol);

    if(sock_peer == INVALID_SOCKET){
        fprintf(stderr, "An error has ocurred while creating socket (%d)", WSAGetLastError());
        exit(EXIT_FAILURE);
    }


    if(connect(sock_peer, tar->ai_addr, (int) tar ->ai_addrlen)){
        fprintf(stderr, "Couldn't connect to host");
        return 0;
    }

    char host_name[MAX_LEN];
    char port_name[MAX_LEN];
    getnameinfo(tar -> ai_addr,
                (int)tar->ai_addrlen,
                host_name,
                MAX_LEN,
                port_name,
                MAX_LEN,
                NI_NUMERICHOST | NI_NUMERICSERV);

    printf("Connected to:\nhost:%s\nport:%s",host_name, port_name);
    freeaddrinfo(tar);

    return sock_peer;
}

void send_request_GET(SOCKET s, char *hostname, char *port, char *path){

}