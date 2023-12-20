//
//  connection.c
//  Client
//

#include "connection.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int init_conn(const char *address){
    int sock;
    
    int tentative = 0;
    
    while (1) {
        
        sock = socket (AF_INET, SOCK_STREAM, 0);
        
        if(sock == -1){
            perror("socket()");
            exit(errno);
        }
        
        struct sockaddr_in sin = {0};
        
        sin.sin_addr.s_addr = inet_addr(address);
        sin.sin_port = htons(1994);
        sin.sin_family = AF_INET;
        
        if (connect(sock, (struct sockaddr *)&sin, sizeof(struct sockaddr)) == -1)
        {
            perror("connection()");
            close(sock);
            
            tentative += 1;
            printf("Tentative numéro : %d - Retrying in 1 minute...\n", tentative);
            sleep(60); // Attendre 1 minute avant la prochaine tentative
        }else{
            printf("Connected to the server.\n");
            break; // Sortir de la boucle si la connexion réussit
        }
    }
    
    return sock;
}

void end_connection(int sock){
    close(sock);
}
