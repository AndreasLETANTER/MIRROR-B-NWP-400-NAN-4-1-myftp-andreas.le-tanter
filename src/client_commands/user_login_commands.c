/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** user_login_command
*/

#include <string.h>
#include <unistd.h>

void handleUSERCommand()
{
    write(1, "USER command\n", strlen("USER command\n"));
}

void handlePASSCommand()
{
    write(1, "PASS command\n", strlen("PASS command\n"));
}

void handleQUITCommand()
{
    write(1, "QUIT command\n", strlen("QUIT command\n"));
}
