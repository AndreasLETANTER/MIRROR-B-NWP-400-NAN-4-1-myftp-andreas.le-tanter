/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** data_transfer_commands
*/

#include <string.h>
#include <unistd.h>
#include "server.h"

void handle_dele_command(int sd, socket_info_s *_socket_info, char *arg)
{
    write(1, "DELE command\n", strlen("DELE command\n"));
}

void handle_list_command(int sd, socket_info_s *_socket_info, char *arg)
{
    write(1, "LIST command\n", strlen("LIST command\n"));
}

void handle_retr_command(int sd, socket_info_s *_socket_info, char *arg)
{
    write(1, "RETR command\n", strlen("RETR command\n"));
}

void handle_stor_command(int sd, socket_info_s *_socket_info, char *arg)
{
    write(1, "STOR command\n", strlen("STOR command\n"));
}
