//
//  read.h
//  Client
//


#ifndef read_h
#define read_h

#define BUFFER_SIZE 1024

extern fd_set rdfs;

int read_from_server(int sock, char *buffer);
void keyboard_fd_listener(void);
void socket_fd_listener(int sock);
int keyboard_fd_received(char (*buffer)[BUFFER_SIZE]);
int socket_fd_received(int sock, char (*buffer)[BUFFER_SIZE]);

#endif /* read_h */
