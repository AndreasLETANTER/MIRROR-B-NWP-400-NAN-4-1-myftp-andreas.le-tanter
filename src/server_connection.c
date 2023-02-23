/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** server_connection
*/

#include "server_connection.h"
#include "client_handling.h"

void seek_connection(socket_info_s *_socket_info)
{
    while(1) {
        accept_connection(_socket_info);
        close(_socket_info->new_socket);
    }
}

void accept_connection(socket_info_s *_socket_info)
{
    fd_set rfds;
    int retval = 0;

    FD_ZERO(&rfds);
    FD_SET(_socket_info->server_fd, &rfds);

    retval = select(_socket_info->server_fd + 1, &rfds, NULL, NULL, NULL);

    if (retval == -1) {
        perror("select() failed");
        exit(EXIT_FAILURE);
    }

    if (FD_ISSET(_socket_info->server_fd, &rfds)) {
        handle_socket(_socket_info);
    }
}
