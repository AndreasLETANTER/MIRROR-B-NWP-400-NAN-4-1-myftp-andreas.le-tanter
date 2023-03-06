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

bool is_logged(int sd_idx, socket_info_s *_socket_info)
{
    if (_socket_info->client_socket[sd_idx]->is_logged == true) {
        return (true);
    }
    return (false);
}

void handle_user_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;

    if (arg == NULL) {
        custom_write(sd, "331 User name okay, need password.\n");
        return;
    }

    if (_socket_info->client_socket[sd_idx]->current_user != NULL)
        free(_socket_info->client_socket[sd_idx]->current_user);
    _socket_info->client_socket[sd_idx]->current_user = strdup(arg);
    custom_write(sd, "331 User name okay, need password.\n");
}

void check_login(int sd_idx, socket_info_s *_socket_info)
{
    if (_socket_info->client_socket[sd_idx]->is_logged == true) {
        return;
    }
    if (strcmp(_socket_info->client_socket[sd_idx]->current_user,
        "Anonymous") == 0
        && _socket_info->client_socket[sd_idx]->current_pswd == NULL) {
        _socket_info->client_socket[sd_idx]->is_logged = true;
        custom_write(_socket_info->client_socket[sd_idx]->socket_fd,
            "230 User logged in, proceed.\n");
    } else {
        custom_write(_socket_info->client_socket[sd_idx]->socket_fd,
            "530 Not logged in.\n");
    }
}

void handle_pass_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;
    char *nextparam = strtok(NULL, " ");

    if (_socket_info->client_socket[sd_idx]->current_pswd != NULL) {
        free(_socket_info->client_socket[sd_idx]->current_pswd);
    } else if (_socket_info->client_socket[sd_idx]->current_user == NULL) {
        custom_write(sd, "332 Need account for login.\n");
        return;
    }
    if (arg == NULL) {
        custom_write(sd, "331 Password okay.\n");
        check_login(sd_idx, _socket_info);
        return;
    }
    _socket_info->client_socket[sd_idx]->current_pswd = strdup(arg);
    custom_write(sd, "331 Password okay.\n");
    check_login(sd_idx, _socket_info);
}

void handle_quit_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;

    quit_engine(sd_idx, _socket_info, arg);
}
