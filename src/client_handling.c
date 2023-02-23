/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** client_handling
*/

#include "client_handling.h"

void handle_socket(socket_info_s *_socket_info)
{
    int new_socket = accept(_socket_info->server_fd, (struct sockaddr*) &_socket_info->address, &_socket_info->addrlen);
    char buff[1024] = { 0 };

    if (new_socket == -1) {
        perror("accept() failed");
        exit(EXIT_FAILURE);
    }
    printf("Connection from %s:%i\n", inet_ntoa(_socket_info->address.sin_addr), ntohs(_socket_info->address.sin_port));
    read(new_socket, buff, 1024);
    write(new_socket, buff, strlen(buff));

    _socket_info->new_socket = new_socket;
}
