/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** data_transfer_commands
*/

#include <string.h>
#include <unistd.h>
#include "server.h"
#include "client_commands.h"

void handle_dele_command(int sd, socket_info_s *_socket_info, char *arg)
{
    write(1, "DELE command\n", strlen("DELE command\n"));
}

void handle_list_command(int sd, socket_info_s *_socket_info, char *arg)
{
    write(1, "LIST command\n", strlen("LIST command\n"));
}

void handle_retr_command(int sd, socket_info_s *_socket_info, char *arg)
{
    for (int i = 0; i < 1024; i++) {
        if (_socket_info->client_socket[i]->socket_fd == sd) {
            retr_engine(sd, _socket_info, arg);
            return;
        }
    }
}

void handle_stor_command(int sd, socket_info_s *_socket_info, char *arg)
{
    write(1, "STOR command\n", strlen("STOR command\n"));
}
