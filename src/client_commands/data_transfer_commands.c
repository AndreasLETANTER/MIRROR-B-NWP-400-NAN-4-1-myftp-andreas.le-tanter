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

void dele_engine(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;
    char *next_arg = strtok(NULL, " ");
    int return_value = 0;

    if (next_arg != NULL) {
        custom_write(sd, "500 Syntax error, command unrecognized.\n");
        return;
    }
    return_value = remove(arg);
    if (return_value == 0)
        custom_write(sd, "250 Requested file action okay, completed.\n");
    else
        custom_write(sd, "550 Requested action not taken.\n");
}

void handle_dele_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    dele_engine(sd_idx, _socket_info, arg);
}

void handle_list_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    list_engine(sd_idx, _socket_info, arg);
}

void handle_retr_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    retr_engine(sd_idx, _socket_info, arg);
}

void handle_stor_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;

    write(1, "STOR command\n", strlen("STOR command\n"));
}
