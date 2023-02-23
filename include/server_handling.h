/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** server_handling
*/

#pragma once
#include "server.h"

void shutdown_server(socket_info_s *_socket_info);
void server_engine(char *port);