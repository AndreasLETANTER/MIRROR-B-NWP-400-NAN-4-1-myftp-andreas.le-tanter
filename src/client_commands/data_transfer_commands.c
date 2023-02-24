/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** data_transfer_commands
*/

#include <string.h>
#include <unistd.h>

void handleDELECommand()
{
    write(1, "DELE command\n", strlen("DELE command\n"));
}

void handleLISTCommand()
{
    write(1, "LIST command\n", strlen("LIST command\n"));
}

void handleRETRCommand()
{
    write(1, "RETR command\n", strlen("RETR command\n"));
}

void handleSTORCommand()
{
    write(1, "STOR command\n", strlen("STOR command\n"));
}
