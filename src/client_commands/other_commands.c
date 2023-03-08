/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** other_commands
*/

#include <string.h>
#include <unistd.h>
#include "server.h"
#include "client_commands.h"

void handle_help_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    help_engine(sd_idx, _socket_info, arg);
}

void handle_noop_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;

    custom_write(sd, "200 Command okay.\n");
}
