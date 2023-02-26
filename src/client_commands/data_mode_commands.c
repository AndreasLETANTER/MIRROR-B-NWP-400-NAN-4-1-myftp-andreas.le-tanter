/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** data_transfer_commands
*/

#include "server.h"
#include "client_handling.h"
#include <string.h>
#include <unistd.h>

int bind_data_socket(int data_sd, char *clientAdress)
{
    struct sockaddr_in address;

    
    inet_pton(AF_INET, clientAdress, &(address.sin_addr));
    address.sin_port = htons(0);

    if (bind(data_sd,
        (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("bind failed\n");
        exit(EXIT_FAILURE);
    }
    printf("port number %d\n", ntohs(address.sin_port));

    listen(data_sd, 3);
    return (data_sd);
}

void handlePASVCommand(int sd, socket_info_s *_socket_info)
{
    write(1, "PASV command\n", strlen("PASV command\n"));
    int data_sd = create_socket();
    char *clientIp = getClientAdress(sd);

    data_sd = bind_data_socket(data_sd, clientIp);
    
    write(sd, clientIp, strlen(clientIp));
    free(clientIp);
}

void handlePORTCommand()
{
    write(1, "PORT command\n", strlen("PORT command\n"));
}
