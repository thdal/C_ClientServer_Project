//
//  network_utils.c
//  Server
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void extractClientIPAddress(int socketDescriptor) {
    struct sockaddr_in clientAddress;
    socklen_t addressSize = sizeof(struct sockaddr_in);

    // Récupérer l'adresse du pair (client)
    int result = getpeername(socketDescriptor, (struct sockaddr *)&clientAddress, &addressSize);

    if (result == 0) {
        // Allouer de la mémoire pour stocker l'adresse IP
        char clientIP[INET_ADDRSTRLEN];

        // Convertir l'adresse IP binaire en format lisible
        const char *ipString = inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);
        int clientPort = ntohs(clientAddress.sin_port);

        if (ipString != NULL) {
            // Faire quelque chose avec l'adresse IP et le PORT
            printf("Client connected from IP: %s, Port: %d\n", clientIP, clientPort);
        } else {
            // Gestion d'erreur si la conversion échoue
            perror("inet_ntop");
        }
    } else {
        // Gestion d'erreur si la récupération de l'adresse échoue
        perror("getpeername");
    }
}
