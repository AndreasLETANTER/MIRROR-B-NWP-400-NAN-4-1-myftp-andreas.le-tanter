/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** client_handling
*/

#pragma once
#include "server.h"

void handle_client_socket(socket_info_s *_socket_info, fd_set rfds);
char *getClientAdress(int sd);
