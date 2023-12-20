//
//  client.c
//  Client
//

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//External files
#include "connection.h"
#include "write.h"
#include "read.h"

#include "client.h"

#define BUFFER_SIZE 1024


static void handler(const char *address, const char *string){
    int sock = init_conn(address);

    char buffer[BUFFER_SIZE];
    
    write_to_server(sock, string);
    
    while(1)
    {
        keyboard_fd_listener();
        socket_fd_listener(sock);
        
        if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            perror("select()");
            exit(errno);
            break;
        }
        
        if(keyboard_fd_received(&buffer)){// If something from keyboard is received
            //write_to_server(sock, string);
            puts(buffer);
        }else if(socket_fd_received(sock, &buffer)){// If something from socket is received
            puts(buffer);
        }
    }
    
    end_connection(sock);
    
}


int main(int argc, const char * argv[]) {
 
    handler("127.0.0.1", "hello");
        
    return 0;
}
