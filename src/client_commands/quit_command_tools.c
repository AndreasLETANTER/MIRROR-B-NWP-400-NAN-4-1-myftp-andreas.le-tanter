/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** quit_command_tools
*/

#include <string.h>
#include <unistd.h>
#include "server.h"
#include "initialyze_client.h"

void quit_engine(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;

    if (arg != NULL) {
        custom_write(sd, "500 Syntax error, command unrecognized.\n");
        return;
    }

    custom_write(sd, "221 Service closing control connection.\n");
    close(_socket_info->client_socket[sd_idx]->socket_fd);
    reset_client(_socket_info, sd_idx, 0);
    free(_socket_info->client_socket[sd_idx]->current_directory);
}
