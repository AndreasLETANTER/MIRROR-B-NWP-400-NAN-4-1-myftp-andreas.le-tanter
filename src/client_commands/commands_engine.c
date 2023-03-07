/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** function_pointer
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "server.h"
#include "client_commands.h"

const char *COMMAND_NAME[] = {
    "USER", "PASS", "CWD", "CDUP", "QUIT", "DELE",
        "PWD", "PASV", "PORT", "HELP", "NOOP", "RETR", "STOR", "LIST", 0
};

void (*ftpCommands[])() = {
    handle_user_command,
    handle_pass_command,
    handle_cwd_command,
    handle_cdup_command,
    handle_quit_command,
    handle_dele_command,
    handle_pwd_command,
    handle_pasv_command,
    handle_port_command,
    handle_help_command,
    handle_noop_command,
    handle_retr_command,
    handle_stor_command,
    handle_list_command
};

int seekcommand(char *userInput, int sd_idx, socket_info_s *_socket_info)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;
    char *command = strtok(userInput, " ");
    char *arg = strtok(NULL, " ");

    if (command == NULL) {
        return (84);
    } else if (is_logged(sd_idx, _socket_info) != true &&
        strcmp("USER", command) != 0 && strcmp(command, "PASS") != 0) {
        custom_write(sd, "530 Not logged in.\n");
        return (84);
    }

    for (int i = 0; COMMAND_NAME[i] != 0; i++) {
        if (strcmp(COMMAND_NAME[i], command) == 0) {
            ftpCommands[i](sd_idx, _socket_info, arg);
            return (0);
        }
    }
    custom_write(sd, "500 Syntax error, command unrecognized.\n");
    return (84);
}
