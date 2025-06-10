#include <stdio.h>
#include "header.h"
#include "auxfunc.h"

int main() {


    char buffer[1024];

    char url[] = "http://www.example.com:80/res/page1.php?user=bob#account\0";
    char **protocol;
    char **hostname = malloc(sizeof(char *));
    char **port = malloc(sizeof(char *));
    char **path = malloc(sizeof(char *));

    parse_url(url, hostname, port, path);
    printf("%s\n%s\n%s", *hostname, *port, *path);

    return 0;
}
