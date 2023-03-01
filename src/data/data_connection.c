/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** data_connection
*/

#include "server.h"

void check_data_interaction(char *buff, int new_socket, int data_socket,
    socket_info_s *_socket_info)
{
    write(new_socket, buff, strlen(buff));
}

void accept_data_connection(socket_info_s *_socket_info, int data_socket)
{
    int new_socket = accept(data_socket,
        (struct sockaddr*) &_socket_info->address, &_socket_info->addrlen);

    if (new_socket == -1) {
        perror("accept() failed");
        exit(EXIT_FAILURE);
    }

    char buff[1024] = { 0 };

    while (1) {
        read(new_socket, buff, 1024);
        check_data_interaction(buff, new_socket, data_socket, _socket_info);
    }
}

void seek_data_socket_entrance(socket_info_s *_socket_info, int data_socket)
{
    while (1) {
        accept_data_connection(_socket_info, data_socket);
    }
}
