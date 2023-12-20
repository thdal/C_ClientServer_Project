//
//  connection.c
//  Server
//

#include "connection.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int init_conn(void){
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sin = {0};

    if(sock == -1)
    {
      perror("socket()");
      exit(errno);
    }

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(1994);
    sin.sin_family = AF_INET;

    if(bind(sock,(struct sockaddr*) &sin, sizeof sin) == -1)
    {
      perror("bind()");
      exit(errno);
    }

    if(listen(sock, 100) == -1)
    {
      perror("listen()");
      exit(errno);
    }

    return sock;
}

void end_connection(int sock){
    close(sock);
}
