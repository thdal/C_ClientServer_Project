//
//  read.h
//  Server
//

#ifndef read_h
#define read_h

extern fd_set rdfs;

#include "client_manager.h"

int read_from_client(int sock, char *buffer);
void keyboard_fd_listener(void);
void socket_fd_listener(int sock);
int keyboard_fd_received(char (*buffer)[BUFFER_SIZE]);
int socket_fd_received(int sock, char (*buffer)[BUFFER_SIZE]);
int new_client_socket_fd_received(int sock, char (*buffer)[BUFFER_SIZE], int *csock);

#endif /* read_h */
