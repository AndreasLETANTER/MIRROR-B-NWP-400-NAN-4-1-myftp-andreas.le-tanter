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

int seekcommand(char *userInput, int sd, socket_info_s *_socket_info)
{
    for (int i = 0; COMMAND_NAME[i] != 0; i++) {
        if (strcmp(COMMAND_NAME[i], userInput) == 0) {
            write(sd, "200 Command okay.\n", strlen("200 Command okay.\n"));
            ftpCommands[i](sd, _socket_info);
            return (0);
        }
    }
    write(sd, "xxx Error (RFC compliant)\n",
        strlen("xxx Error (RFC compliant)\n"));
    return (84);
}
