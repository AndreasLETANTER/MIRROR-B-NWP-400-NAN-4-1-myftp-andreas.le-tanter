/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** user_login_command
*/

#include <string.h>
#include <unistd.h>
#include "server.h"
#include "client_commands.h"

void handle_user_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;

    _socket_info->client_socket[sd_idx]->current_user = strdup(arg);
    custom_write(sd, "331 User name okay, need password.\n");
}

void handle_pass_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;

    write(1, "PASS command\n", strlen("PASS command\n"));
}

void handle_quit_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;

    quit_engine(sd_idx, _socket_info, arg);
}
