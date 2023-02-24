/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** directory_handling_commands
*/

#include <string.h>
#include <unistd.h>

void handleCWDCommand()
{
    write(1, "CWD command\n", strlen("CWD command\n"));
}

void handleCDUPCommand()
{
    write(1, "CDUP command\n", strlen("CDUP command\n"));
}

void handlePWDCommand()
{
    write(1, "PWD command\n", strlen("PWD command\n"));
}
