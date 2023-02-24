/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** other_commands
*/

#include <string.h>
#include <unistd.h>

void handleHELPCommand()
{
    write(1, "HELP command\n", strlen("HELP command\n"));
}

void handleNOOPCommand()
{
    write(1, "NOOP command\n", strlen("NOOP command\n"));
}
