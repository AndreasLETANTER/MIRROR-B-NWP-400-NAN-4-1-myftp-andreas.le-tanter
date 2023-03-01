/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** data_transfer_commands
*/

#include "server.h"
#include "data_connection.h"
#include "client_handling.h"
#include <string.h>
#include <unistd.h>

void displayipandport(struct sockaddr_in address, int sd)
{
    unsigned char *p = (unsigned char *) &address.sin_addr.s_addr;
    int p1 = p[0];
    int p2 = p[1];
    int p3 = p[2];
    int p4 = p[3];
    int port = ntohs(address.sin_port);
    int port_high_byte = port / 256;
    int port_low_byte = port % 256;
    char response[50];

    sprintf(response, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)\n",
        p1, p2, p3, p4, port_high_byte, port_low_byte);
    write(sd, response, strlen(response));
    sprintf(response, "\033[1;34m[DEBUG]: Data port is %d\033[0m\n", port);
    write(2, response, strlen(response));
}

int bind_data_socket(int sd, int data_sd, char *clientAdress)
{
    struct sockaddr_in address;

    inet_pton(AF_INET, clientAdress, &(address.sin_addr));
    address.sin_port = htons(0);

    if (bind(data_sd,
        (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("bind failed\n");
        exit(EXIT_FAILURE);
    }
    socklen_t len = sizeof(address);
    getsockname(data_sd, (struct sockaddr *) &address, &len);

    displayipandport(address, sd);

    listen(data_sd, 1);
    return (data_sd);
}

void handle_pasv_command(int sd, socket_info_s *_socket_info)
{
    int data_sd = create_socket();
    char *clientIp = getclientadress(sd);

    data_sd = bind_data_socket(sd, data_sd, clientIp);

    for (int i = 0; i < 1024; i++) {
        if (_socket_info->client_socket[i]->socket_fd == 0) {
            _socket_info->client_socket[i]->socket_fd = data_sd;
            _socket_info->client_socket[i]->socket_type = DATASOCKET;
            break;
        }
    }

    if (fork() == 0)
        seek_data_socket_entrance(_socket_info, data_sd);

    free(clientIp);
}

void handle_port_command(int sd, socket_info_s *_socket_info)
{
    write(1, "PORT command\n", strlen("PORT command\n"));
}
