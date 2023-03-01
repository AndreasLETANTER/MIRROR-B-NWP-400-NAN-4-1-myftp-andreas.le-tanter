/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** data_connection
*/

#pragma once

void check_data_interaction(char *buff, int new_socket, int data_socket,
    socket_info_s *_socket_info);
void seek_data_socket_entrance(socket_info_s *_socket_info, int data_socket);
void accept_data_connection(socket_info_s *_socket_info, int data_socket);