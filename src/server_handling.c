/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** server_handling
*/

#include "server_handling.h"
#include "server_connection.h"

void shutdown_server(socket_info_s *_socket_info)
{
    close(_socket_info->server_fd);
    shutdown(_socket_info->server_fd, SHUT_RDWR);
}

void server_engine(char *port)
{
    struct socket_info_t _socket_info;

    initialyze_server(&_socket_info, port);
    seek_connection(&_socket_info);
    shutdown_server(&_socket_info);
}
