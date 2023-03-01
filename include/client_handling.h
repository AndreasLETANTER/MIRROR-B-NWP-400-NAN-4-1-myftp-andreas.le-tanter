/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** client_handling
*/

#pragma once
#include "server.h"

void handle_client_socket(socket_info_s *_socket_info, fd_set rfds);
char *getclientadress(int sd);
int get_data_client(socket_info_s *_socket_info, int sd);
int get_data_socket(socket_info_s *_socket_info, int sd);
void remove_data(socket_info_s *_socket_info, int sd);
