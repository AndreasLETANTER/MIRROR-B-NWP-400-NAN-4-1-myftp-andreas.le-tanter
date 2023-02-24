/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** initialyze_server
*/

#include "server.h"

int create_socket(void)
{
    int server_fd = 0;
    int opt = 1;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(84);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
        sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

void bind_socket(socket_info_s *_socket_info, int port)
{
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    if (bind(_socket_info->server_socket->socket_fd,
        (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("bind failed\n");
        exit(EXIT_FAILURE);
    }
    _socket_info->address = address;
}

void initialyze_queue(socket_info_s *_socket_info)
{
    if (listen(_socket_info->server_socket->socket_fd, 3) < 0) {
        perror("listen failed\n");
        exit(EXIT_FAILURE);
    }
}

void initialyze_server(socket_info_s *_socket_info, char *port)
{
    _socket_info->server_socket = malloc(sizeof(socket_s));
    _socket_info->server_socket->socket_fd = create_socket();
    bind_socket(_socket_info, atoi(port));
    initialyze_queue(_socket_info);

    for (int i = 0; i < 1024; i++) {
        _socket_info->client_socket[i] = 0;
    }

    _socket_info->addrlen = sizeof(_socket_info->address);
    printf("Server started on port %s\n", port);
}
