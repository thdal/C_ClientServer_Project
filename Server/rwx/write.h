//
//  write.h
//  Server
//

#ifndef write_h
#define write_h

#include "client_manager.h"

void write_to_client(int sock, const char *buffer);
void write_message_to_all_clients(Client *clients, Client sender, int actual, const char *buffer, char from_server);

#endif /* write_h */
