//
//  write.c
//  Client
//

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

//External files
#include "write.h"

void write_to_server(int sock, const char *buffer)
{
    if(send(sock, buffer, strlen(buffer),0) < 0 )
    {
        perror("send()");
        exit(errno);
    }
}
