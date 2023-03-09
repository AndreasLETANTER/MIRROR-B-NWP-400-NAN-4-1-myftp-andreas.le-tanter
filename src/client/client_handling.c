/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** client_handling
*/

#include "server.h"
#include <stdbool.h>
#include "client_connection.h"
#include <stdio.h>
#include "client_tools.h"

void handle_buffer(int i, socket_info_s *_socket_info, int sd)
{
    int valread = 0;
    char buffer[1024] = { 0 };

    while (buffer[strlen(buffer) - 1] != '\n'
        && buffer[strlen(buffer) - 2] != '\r') {
        valread = read(sd, buffer + strlen(buffer), 1024);
    }
    check_client_interaction(buffer, valread, i, _socket_info);
}

void handle_client_socket(socket_info_s *_socket_info, fd_set rfds)
{
    for (int i = 0, sd = 0; i < 1024; i++) {
        sd = _socket_info->client_socket[i]->socket_fd;

        if (_socket_info->client_socket[i]->socket_type
                == CLIENTSOCKET && FD_ISSET(sd, &rfds)) {
            handle_buffer(i, _socket_info, sd);
        }
    }
}
