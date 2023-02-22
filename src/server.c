/*
** EPITECH PROJECT, 2023
** bootstrap_my_ftp [WSL : Ubuntu]
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

typedef struct socket_info_t {
    int server_fd;
    int new_socket;
    struct sockaddr_in address;
    int addrlen;
} socket_info_s;

int create_socket()
{
    int server_fd = 0;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(84);
    }
    return server_fd;
}

void bind_socket(socket_info_s *_socket_info, int port)
{
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    
    if (bind(_socket_info->server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("bind failed\n");
        exit(EXIT_FAILURE);
    }
    _socket_info->address = address;
}

void initialyze_queue(socket_info_s *_socket_info)
{
    if (listen(_socket_info->server_fd, 3) < 0) {
        perror("listen failed\n");
        exit(EXIT_FAILURE);
    }
}

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

void initialyze_server(socket_info_s *_socket_info, char *port)
{
    _socket_info->server_fd = create_socket();
    bind_socket(_socket_info, atoi(port));
    initialyze_queue(_socket_info);
}

void shutdown_server(socket_info_s *_socket_info)
{
    close(_socket_info->server_fd);
    shutdown(_socket_info->server_fd, SHUT_RDWR);
}

void seek_connection(socket_info_s *_socket_info)
{
    while(1) {
        accept_connection(_socket_info);
        close(_socket_info->new_socket);
    }
}

int main (int argc, char **argv)
{
    struct socket_info_t _socket_info;

    if (argc == 3) {
        initialyze_server(&_socket_info, argv[1]);
        seek_connection(&_socket_info);
        shutdown_server(&_socket_info);
    }
}
