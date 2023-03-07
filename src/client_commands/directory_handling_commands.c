/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** directory_handling_commands
*/

#include <string.h>
#include <unistd.h>
#include "server.h"

void handle_cwd_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;

    if (arg == NULL) {
        custom_write(sd, "500 Syntax error, command unrecognized.\n");
        return;
    }
    if (chdir(arg) == -1) {
        custom_write(sd, "550 Failed to change directory.\n");
        return;
    }
    free(_socket_info->client_socket[sd_idx]->current_directory);
    _socket_info->client_socket[sd_idx]->current_directory
        = strdup(getcwd(NULL, 0));
    custom_write(sd, "250 Directory successfully changed.\n");
}

void handle_cdup_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;
    char *display = malloc(sizeof(char) * (
            strlen(_socket_info->client_socket[sd_idx]->current_directory)
                + strlen("200 directory changed to ") + 1) + 1);

    if (arg != NULL) {
        custom_write(sd, "500 Syntax error, command unrecognized.\n");
        free(display);
        return;
    }
    display[0] = '\0';
    display = strcat(display, "200 directory changed to ");
    display = strcat(display,
        _socket_info->client_socket[sd_idx]->current_directory);
    display = strcat(display, "\n");
    free(_socket_info->base_directory);
    _socket_info->base_directory =
        strdup(_socket_info->client_socket[sd_idx]->current_directory);
    custom_write(sd, display);
    free(display);
}

void handle_pwd_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;
    char *current_directory = malloc(sizeof(char) *
        (strlen(_socket_info->client_socket[sd_idx]->current_directory) +
            strlen("257 ") + 1) + 1);

    if (arg != NULL) {
        custom_write(sd, "500 Syntax error, command unrecognized.\n");
        free(current_directory);
        return;
    }
    current_directory[0] = '\0';
    current_directory = strcat(current_directory, "257 ");
    current_directory = strcat(current_directory,
        _socket_info->client_socket[sd_idx]->current_directory);
    current_directory = strcat(current_directory, "\n");
    custom_write(sd, current_directory);
    free(current_directory);
}
