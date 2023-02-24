/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** data_transfer_commands
*/

#include <string.h>
#include <unistd.h>

void handlePASVCommand()
{
    write(1, "PASV command\n", strlen("PASV command\n"));
}

void handlePORTCommand()
{
    write(1, "PORT command\n", strlen("PORT command\n"));
}
