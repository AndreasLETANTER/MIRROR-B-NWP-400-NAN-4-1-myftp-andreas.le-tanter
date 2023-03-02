/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** server
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

enum {
    DATASOCKET = 0,
    CLIENTSOCKET = 1,
    SERVERSOCKET = 2
};

typedef struct socket_t {
    int socket_fd;
    int socket_type;
    int data_socket;
    int data_client;
    char *current_user;
    char *current_pswd;
} socket_s;

typedef struct socket_info_t {
    struct socket_t *client_socket[1024];
    struct socket_t *server_socket;
    struct sockaddr_in address;
    char *base_directory;
    char *current_directory;
    int addrlen;
    int max_sd;
} socket_info_s;

int create_socket(void);
void bind_socket(socket_info_s *_socket_info, int port);
void initialyze_queue(socket_info_s *_socket_info);
void initialyze_server(socket_info_s *_socket_info, char *port);
int custom_write(int fd, const char *str);
