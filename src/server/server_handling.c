/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** server_handling
*/

#include "initialyze_client.h"
#include "server_connection.h"
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void shutdown_server(socket_info_s *_socket_info)
{
    close(_socket_info->server_socket->socket_fd);
    shutdown(_socket_info->server_socket->socket_fd, SHUT_RDWR);
    free(_socket_info->base_directory);
    free(_socket_info->server_socket);
}

void initialyze_path(socket_info_s *_socket_info, char *base_directory)
{
    _socket_info->base_directory = malloc(sizeof(char)
        * strlen(base_directory) + 2);
    _socket_info->base_directory[0] = '\0';

    _socket_info->base_directory = strcat(_socket_info->base_directory,
        base_directory);
    if (base_directory[strlen(base_directory) - 1] != '/')
        _socket_info->base_directory =
            strcat(_socket_info->base_directory, "/");
}

void check_for_good_path(char *base_directory)
{
    DIR *directory = opendir(base_directory);

    if (directory) {
        return;
    } else {
        perror("bad path");
        exit(84);
    }
}

void server_engine(char *port, char *base_directory)
{
    struct socket_info_t _socket_info;

    check_for_good_path(base_directory);
    initialyze_path(&_socket_info, base_directory);
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
        exit(84);
    }

    initialyze_client_socket(_socket_info, new_socket);
}
