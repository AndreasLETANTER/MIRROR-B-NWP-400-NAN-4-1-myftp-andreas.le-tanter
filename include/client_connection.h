/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** client_connection
*/

#pragma once
#include "server.h"

bool check_client_deconnection(int sd, int valread,
    socket_info_s *_socket_info, int i);
void check_client_interaction(char *buffer, int valread, int sd
    , socket_info_s *_socket_info);
