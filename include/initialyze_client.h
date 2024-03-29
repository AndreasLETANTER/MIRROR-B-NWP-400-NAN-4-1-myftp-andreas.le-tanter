/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** initialyze_client
*/

#pragma once
#include "server.h"

void initialyze_client_socket(socket_info_s *_socket_info, int new_socket);
void reset_client(socket_info_s *_socket_info, int sd_idx, int new_socket);
void init_all_clients_info(socket_info_s *_socket_info, int i);
