/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** server_handling
*/

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

void handle_server_socket(socket_info_s *_socket_info)
{
    int new_socket = accept(_socket_info->server_fd, (struct sockaddr*) &_socket_info->address, &_socket_info->addrlen);
    char buff[1024] = { 0 };

    if (new_socket == -1) {
        perror("accept() failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Connection from %s:%i\n", inet_ntoa(_socket_info->address.sin_addr), ntohs(_socket_info->address.sin_port));
    write(new_socket, "Welcome\r" , strlen("Welcome\r"));

    for (int i = 0; i < 1024; i++) {
        if (_socket_info->client_socket[i] == 0) {
            _socket_info->client_socket[i] = new_socket;
            printf("Adding to list of sockets as %d\n", i);
            break;
        }
    }
}
