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

typedef struct socket_info_t {
    int server_fd;
    int new_socket;
    struct sockaddr_in address;
    int addrlen;
} socket_info_s;

int create_socket();
void bind_socket(socket_info_s *_socket_info, int port);
void initialyze_queue(socket_info_s *_socket_info);
void initialyze_server(socket_info_s *_socket_info, char *port);
