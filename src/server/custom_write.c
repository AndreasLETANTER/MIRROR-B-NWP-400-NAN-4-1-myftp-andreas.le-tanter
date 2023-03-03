/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** custom_write
*/

#include <string.h>
#include <unistd.h>

int custom_write(int fd, const char *str)
{

    write(2, "\033[1;34m", strlen("\033[1;34m"));
    write(2, str, strlen(str));
    write(2, "\033[0m", strlen("\033[0m\n"));

    return (write(fd, str, strlen(str)));
}
