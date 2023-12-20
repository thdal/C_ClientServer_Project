//
//  client_management.c
//  Server
//

#include <unistd.h>
#include <string.h>

#include "client_manager.h"
#include "client_struct.h"

Client clients[100];
int nbclient = 0;
int csock;

void clear_clients(Client *clients, int nbclient)
{
   int i = 0;
   for(i = 0; i < nbclient; i++)
   {
      close(clients[i].sock);
   }
}

void remove_client(Client *clients, int to_remove, int *nbclient)
{
   // We remove the client from the array */
   memmove(clients + to_remove, clients + to_remove + 1, (*nbclient - to_remove - 1) * sizeof(Client));
   // number client - 1
   (*nbclient)--;
}

void add_client(int csock, const char *buffer){
    Client c = { csock };
    strncpy(c.name, buffer, BUFFER_SIZE - 1);
    clients[nbclient] = c;
    nbclient++;
}
