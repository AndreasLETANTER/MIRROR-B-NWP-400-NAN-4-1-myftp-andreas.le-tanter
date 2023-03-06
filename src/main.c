/*
** EPITECH PROJECT, 2023
** bootstrap_my_ftp [WSL : Ubuntu]
** File description:
** main.c
*/

#include "server.h"
#include "server_handling.h"

int main (int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        printf("USAGE: ./myftp port path\n");
        printf("\tport is the port number on which the server socket listens\n");
        printf("\tpath is the path to the home directory for the Anonymous user\n");
        return (0);
    }
    if (argc == 3) {
        server_engine(argv[1], argv[2]);
        return (0);
    }
    return (84);
}
