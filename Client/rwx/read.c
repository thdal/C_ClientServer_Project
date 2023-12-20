//
//  read.c
//  Client
//

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "read.h"

#define BUFFER_SIZE 1024

fd_set rdfs; // File descriptor reader

int read_from_server(int sock, char *buffer)
{
    int b = 0;
    
    if( (b = recv(sock, buffer, BUFFER_SIZE - 1, 0)) < 0 )
    {
        perror("recv()");
        exit(errno);
    }
    
    buffer[b] = 0;
    
    return b;
}

void keyboard_fd_listener(void){
    FD_ZERO(&rdfs);
    // STDIN_FILENO == keyboard
    FD_SET(STDIN_FILENO, &rdfs); // We listening keyboard io
}

void socket_fd_listener(int sock){
    FD_ZERO(&rdfs);
    FD_SET(sock, &rdfs); // We listening socket io
}

int keyboard_fd_received(char (*buffer)[BUFFER_SIZE] ){
    if(FD_ISSET(STDIN_FILENO, &rdfs)){
        fgets(*buffer, BUFFER_SIZE -1, stdin);
        {
            char *p = NULL;
            p = strstr(*buffer, "\n");
            if( p != NULL)
            {
                *p = 0;
            }
            else
            {
                /* fclean */
                (*buffer)[BUFFER_SIZE - 1] = 0;
            }
        }
        return 1;
    }
    else{
        return 0;
    }
}

int socket_fd_received(int sock, char (*buffer)[BUFFER_SIZE]){
    if (FD_ISSET(sock, &rdfs))
    {
        int b = read_from_server(sock, *buffer);
        
        if(b == 0)//Erreur serveur
        {
            printf("Server disconnected ! \n");
            exit(errno);
        }
        return 1;
    }
    else{
        return 0;
    }
}
