//
//  read.c
//  Server
//

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "read.h"

fd_set rdfs; // File descriptor reader

int read_from_client(int sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUFFER_SIZE - 1, 0)) < 0)
   {
      perror("recv() ici");
      /* if recv error we disonnect the client */
      n = 0;
   }

   buffer[n] = 0;

   return n;
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
        int b = read_from_client(sock, *buffer);
        
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

int new_client_socket_fd_received(int sock, char (*buffer)[BUFFER_SIZE],int *csock){
    if (FD_ISSET(sock, &rdfs))
    {
        // new client
        struct sockaddr_in csin = {0};
        size_t sinsize = sizeof csin;
        *csock = accept(sock, (struct sockaddr*)&csin, &sinsize);
        if(*csock == -1)
        {
            perror("New client connection error()");
            //continue;
        }
        
        int b = read_from_client(*csock, *buffer);
        
        if(b == 0)//Erreur receiving client name
        {
            printf("Client name reception error ! \n");
        }
        
        
        return 1;
    }
    else{
        return 0;
    }
}
