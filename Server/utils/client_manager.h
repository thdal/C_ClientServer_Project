//
//  client_management.h
//  Server
//

#ifndef client_management_h
#define client_management_h

#define BUFFER_SIZE 1024

typedef struct
{
   int sock;
   char name[BUFFER_SIZE];
}Client;

extern Client clients[100];

extern int nbclient;
extern int csock;

void clear_clients(Client *clients, int actual);
void remove_client(Client *clients, int to_remove, int *actual);
void add_client(int csock, const char *buffer);

#endif /* client_management_h */
