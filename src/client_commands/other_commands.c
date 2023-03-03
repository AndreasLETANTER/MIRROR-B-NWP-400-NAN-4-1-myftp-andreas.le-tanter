/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** other_commands
*/

#include <string.h>
#include <unistd.h>
#include "server.h"

void handle_help_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;

    write(1, "HELP command\n", strlen("HELP command\n"));
}

void handle_noop_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;

    write(1, "NOOP command\n", strlen("NOOP command\n"));
}
