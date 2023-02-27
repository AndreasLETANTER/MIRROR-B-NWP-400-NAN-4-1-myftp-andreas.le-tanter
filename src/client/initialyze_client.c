/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** initialyze_client
*/

#include "server.h"

void initialyze_client_socket(socket_info_s *_socket_info, int new_socket)
{
    printf("Connection from %s:%i\n",
        inet_ntoa(_socket_info->address.sin_addr),
            ntohs(_socket_info->address.sin_port));
    write(new_socket, "220 Service ready for new user.\n"
        , strlen("220 Service ready for new user.\n"));

    for (int i = 0; i < 1024; i++) {
        if (_socket_info->client_socket[i]->socket_fd == 0) {
            _socket_info->client_socket[i]->socket_fd = new_socket;
            _socket_info->client_socket[i]->socket_type = CLIENTSOCKET;
            printf("Adding to list of sockets as %d\n", i);
            break;
        }
    }
}
