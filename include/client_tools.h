/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** client_tools
*/

#pragma once

char *getclientadress(int sd);
void remove_data(socket_info_s *_socket_info, int sd);
int get_data_socket(socket_info_s *_socket_info, int sd);
int get_data_client(socket_info_s *_socket_info, int sd);
