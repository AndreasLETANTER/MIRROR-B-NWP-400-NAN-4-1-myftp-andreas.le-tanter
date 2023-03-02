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
    if (argc == 3) {
        server_engine(argv[1], argv[2]);
        return (0);
    }
    return (84);
}
