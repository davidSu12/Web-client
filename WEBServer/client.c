#include "header.h"


/*
 * Warning of advice:
 * This piece of software is just developed under learning purpose
 * in concrete, a desire of learning the windows API of sockets altough
 * it's specified in the header to be portable across plataforms I tend
 * to use only the calling functions that are owned by the api of windows.
 */



int main(int argc, char **argv){

    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2), &d)){
        fprintf(stderr, "Ane error has ocurred while doing the startup (%d)", WSAGetLastError());
        exit(EXIT_FAILURE);
    }


    return 0;
}