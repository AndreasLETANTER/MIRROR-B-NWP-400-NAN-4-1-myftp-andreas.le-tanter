/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** server_connection
*/

#include "client_handling.h"
#include "server_handling.h"

void accept_connection(socket_info_s *_socket_info)
{
    fd_set rfds;
    int activity = 0;

    FD_ZERO(&rfds);
    FD_SET(_socket_info->server_fd, &rfds);
    _socket_info->max_sd = _socket_info->server_fd;

    for (int i = 0, sd = 0; i < 1024; i++) {
        sd = _socket_info->client_socket[i];
        if (sd > 0)
            FD_SET(sd, &rfds);
        if (sd > _socket_info->max_sd)
            _socket_info->max_sd = sd;
    }

    activity = select(_socket_info->max_sd + 1, &rfds, NULL, NULL, NULL);

    if (activity == -1) {
        perror("select() failed");
        exit(EXIT_FAILURE);
    }

    if (FD_ISSET(_socket_info->server_fd, &rfds)) {
        handle_server_socket(_socket_info);
    }

    handle_client_socket(_socket_info, rfds);
}

void seek_connection(socket_info_s *_socket_info)
{
    while(1) {
        accept_connection(_socket_info);
    }

}
