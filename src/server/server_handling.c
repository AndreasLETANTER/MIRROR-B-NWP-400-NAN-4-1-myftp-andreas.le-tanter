/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** server_handling
*/

#include "initialyze_client.h"
#include "server_connection.h"

void shutdown_server(socket_info_s *_socket_info)
{
    close(_socket_info->server_socket->socket_fd);
    shutdown(_socket_info->server_socket->socket_fd, SHUT_RDWR);
    free(_socket_info->server_socket);
}

void server_engine(char *port)
{
    struct socket_info_t _socket_info;

    initialyze_server(&_socket_info, port);
    seek_connection(&_socket_info);
    shutdown_server(&_socket_info);
}

void handle_server_socket(socket_info_s *_socket_info)
{
    int new_socket = accept(_socket_info->server_socket->socket_fd,
        (struct sockaddr*) &_socket_info->address, &_socket_info->addrlen);
    char buff[1024] = { 0 };

    if (new_socket == -1) {
        perror("accept() failed");
        exit(EXIT_FAILURE);
    }

    initialyze_client_socket(_socket_info, new_socket);
}
