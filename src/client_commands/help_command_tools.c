/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** help_command_tools
*/

#include <string.h>
#include <unistd.h>
#include "server.h"
#include "client_commands.h"

void handle_no_arg_help(int sd)
{
    custom_write(sd, "214 here are the commands recognized :\
        \n\tUSER\n\tPASS\n\tCWD\n\tCDUP\n\tQUIT\n\tDELE\n\tPWD\
        \n\tPASV\n\tPORT\n\tHELP\n\tNOOP\n\tRETR\n\tSTOR\n\tLIST\n");
}

void help_engine(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;
    char *next_arg = strtok(NULL, " ");

    if (next_arg != NULL) {
        custom_write(sd, "500 Syntax error, command unrecognized.\n");
        return;
    }
    if (arg == NULL) {
        handle_no_arg_help(sd);
    }
}
