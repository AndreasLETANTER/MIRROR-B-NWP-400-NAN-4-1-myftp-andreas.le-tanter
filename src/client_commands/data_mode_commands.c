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

int bind_data_socket(int sd, int data_sd, char *clientAdress, int socket)
{
    struct sockaddr_in address;

    inet_pton(AF_INET, clientAdress, &(address.sin_addr));
    address.sin_port = htons(socket);

    if (bind(data_sd,
        (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("bind failed\n");
        exit(84);
    }
    socklen_t len = sizeof(address);
    getsockname(data_sd, (struct sockaddr *) &address, &len);

    displayipandport(address, sd);

    listen(data_sd, 1);
    return (data_sd);
}

void seek_data_connection(socket_info_s *_socket_info, int data_sd, int sd)
{
    int new_socket = accept(data_sd,
        (struct sockaddr*) &_socket_info->address, &_socket_info->addrlen);
    char buff[1024] = { 0 };

    if (new_socket == -1) {
        perror("accept() failed");
        exit(84);
    }

    for (int i = 0; i < 1024; i++) {
        if (_socket_info->client_socket[i]->socket_fd == sd) {
            _socket_info->client_socket[i]->data_socket = data_sd;
            _socket_info->client_socket[i]->data_client = new_socket;
            break;
        }
    }
}

void handle_pasv_command(int sd, socket_info_s *_socket_info, char *arg)
{
    int data_sd = create_socket();
    char *clientIp = getclientadress(sd);

    if (arg != NULL)
        custom_write(sd, "504 Command not implemented for that parameter.\n");

    data_sd = bind_data_socket(sd, data_sd, clientIp, 0);

    if (fork() == 0)
        seek_data_connection(_socket_info, data_sd, sd);

    free(clientIp);
}

void handle_port_command(int sd, socket_info_s *_socket_info, char *arg)
{
    write(1, "PORT command\n", strlen("PORT command\n"));
}
