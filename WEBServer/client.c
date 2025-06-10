#include "header.h"
#include "auxfunc.h"
#include "client_API.h"

/*
 * Warning of advice:
 * This piece of software is just developed under learning purpose
 * in concrete, a desire of learning the windows API of sockets altough
 * it's specified in the header to be portable across plataforms I tend
 * to use only the calling functions that are owned specifically by microsoft.
 */



int main(int argc, char **argv){

    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2), &d)){
        fprintf(stderr, "Ane error has ocurred while doing the startup (%d)", WSAGetLastError());
        exit(EXIT_FAILURE);
    }


    if(argc < 2){
        fprintf(stderr, "usage: web_get url\n");
        return -1;
    }

    char *url = argv[1];

    char *hostname, *port, *path;
    parse_url(url, &hostname, &port, &path);

    SOCKET server = connect_to_host(hostname, port);
    send_request_GET(server, hostname, port, path);

    const clock_t start_time = clock();

#define RESPONSE_SIZE 8192

    char response[RESPONSE_SIZE+1];
    char *p = response, *q;
    char *end = response + RESPONSE_SIZE;
    char *body;

    enum{length, chunked, connection};
    int encoding = 0;
    int remaining = 0;


    while(1){

        if((clock() -  start_time) / CLOCKS_PER_SEC > TIMEOUT){
            //if it passes some time then the connection is closed

            fprintf(stderr, "timeouf after %.2f seconds", TIMEOUT);
            return -1;
        }

        if(p == end){


            fprintf(stderr, "out of buffer space\n");
            return -1;
        }


        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(server, &reads);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 200000;

        if(select(server + 1, &reads, 0, 0, &timeout) < 0){
            fprintf(stderr, "select() failed %d", WSAGetLastError());
            return -1;
        }

        if(FD_ISSET(server, &reads)){

            //we are ready to read
            int bytes_received = recv(server, p, end - p, 0);
            if(bytes_received < 1){

                //connection closed by peer
                if((encoding == connection) && body){
                    printf("%.*s", (int)(end - body), body);
                }

                printf("\nConnection closed by peer.\n");
                break;
            }
            p+=bytes_received;
            *p = 0;


            if(!body && (body = strstr(response, "\r\n\r\n"))){
                *body = 0;
                body += 4;
            }

            q = strstr(response, "\nContent-Length: ");
            if(q){
                encoding = length;
                q = strchr(q, ' ');
                q += 1;
                remaining = strtol(q,0, 10);
            }else{
                q = strstr(response, "\nTransfer-Encoding: chunked");
                if(q){
                    encoding = chunked;
                    remaining = 0;
                }else{
                    encoding = connection;
                }
            }
            printf("\nReceived body:\n");

            if(body){
                if(encoding == length){
                    if(p-body >= remaining){
                        printf("%.*s", remaining, body);
                        break;
                    }
                }else if(encoding == chunked){
                    do{
                        if(remaining == 0){
                            if((q = strstr(body, "\r\n"))){
                                //here we just simply get how many bytes are left on the paragraph
                                remaining = strtol(body,0, 16);
                                if(!remaining) goto finish;
                                body = q+2;
                            }else{
                                break;
                            }
                        }
                        if(remaining && (p - body >= remaining)){
                            printf("%.*s", remaining, body);
                            body += remaining + 2;
                            remaining = 0;
                        }
                    }while(!remaining);
                }
            }
        }

    }
finish:

    printf("\nClosing socket");
    closesocket(server);

    WSACleanup();

    return 0;
}