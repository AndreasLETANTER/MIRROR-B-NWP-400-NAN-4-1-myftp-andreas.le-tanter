/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** server_connection
*/

#pragma once
#include "server.h"

void seek_connection(socket_info_s *_socket_info);
void accept_connection(socket_info_s *_socket_info);
void handling_connections(socket_info_s *_socket_info, fd_set rfds);
