//
//  server.c
//  App
//

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//External files
#include "client_manager.h"
#include "connection.h"
#include "write.h"
#include "read.h"
#include "network_utils.h"

#include "server.h"


static void handler(void){
    
    int sock = init_conn();

    char buffer[BUFFER_SIZE];
    
    int max = sock;

    while(1)
    {
        printf("Server listening...\n");

        int i = 0;
        
        keyboard_fd_listener();
        socket_fd_listener(sock);
        
        // Listening all client sock
        for(i = 0; i < nbclient; i++)
        {
            socket_fd_listener(clients[i].sock);
        }
        
        if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            perror("select()");
            exit(errno);
        }
        
        if(keyboard_fd_received(&buffer)){// If something from keyboard is received
            printf("Key pressed. Exit\n");
            break;
        }else if(new_client_socket_fd_received(sock, &buffer, &csock)){// If something from socket is received
            printf("New client received.\n");
            max = csock > max ? csock : max;
            socket_fd_listener(csock);
            add_client(csock, buffer);
            extractClientIPAddress(csock);
            printf("%s just connected.\n", buffer);
        }
        else
        {
            int i = 0;
            for(i = 0; i < nbclient; i++)
            {
                // A client sending something
                if(socket_fd_received(clients[i].sock, &buffer))
                {
                   Client client = clients[i];
                    
                   int c = read_from_client(clients[i].sock, buffer);
                   // Client disconnected
                   if(c == 0)
                   {
                      close(clients[i].sock);
                      remove_client(clients, i, &nbclient);
                      strncpy(buffer, client.name, BUFFER_SIZE - 1);
                      strncat(buffer, " disconnected !", BUFFER_SIZE - strlen(buffer) - 1);
                      write_message_to_all_clients(clients, client, nbclient, buffer, 1);
                   }
                   else
                   {
                       write_message_to_all_clients(clients, client, nbclient, buffer, 0);
                   }
                   break;
                }
            }
        }
    }
    
    clear_clients(clients, nbclient);
    end_connection(sock);
        
}


int main(int argc, const char * argv[]) {
 
    handler();
        
    return 0;
}
