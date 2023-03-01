/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** user_login_command
*/

#include <string.h>
#include <unistd.h>
#include "server.h"

void handle_user_command(int sd, socket_info_s *_socket_info, char *arg)
{
    write(1, "USER command\n", strlen("USER command\n"));
}

void handle_pass_command(int sd, socket_info_s *_socket_info, char *arg)
{
    write(1, "PASS command\n", strlen("PASS command\n"));
}

void handle_quit_command(int sd, socket_info_s *_socket_info, char *arg)
{
    write(1, "QUIT command\n", strlen("QUIT command\n"));
}
