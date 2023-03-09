/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** stor_command_tools
*/

#include "server.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "client_handling.h"

static int check_error(int sd, socket_info_s *_socket_info, char *arg)
{
    int data_socket = get_data_socket(_socket_info, sd);
    int data_client = get_data_client(_socket_info, sd);
    char *nextparam = strtok(NULL, " ");

    if (data_socket == -1) {
        custom_write(sd, "503 Bad sequence of commands\n");
        return -1;
    }
    if (nextparam != NULL) {
        custom_write(sd, "504 Command not implemented for that parameter.\n");
        return -1;
    }
    if (arg == NULL) {
        custom_write(sd, "550 please specify a file to retrieve\n");
        return -1;
    }
    return 0;
}

static char *create_path(char *current_directory, char *arg)
{
    char *path;

    path = malloc(sizeof(char) * (strlen(current_directory)
        + strlen(arg) + 1) + 1);
    path[0] = '\0';
    path = strcat(path, current_directory);
    path = strcat(path, "/");
    path = strcat(path, arg);
    return path;
}

void clean_data(int fd, int sd, socket_info_s *_socket_info)
{
    int data_socket = get_data_socket(_socket_info, sd);
    int data_client = get_data_client(_socket_info, sd);

    close(fd);
    close(data_client);
    close(data_socket);
    remove_data(_socket_info, sd);
}

void write_data(int sd, socket_info_s *_socket_info, int fd)
{
    int data_socket = get_data_socket(_socket_info, sd);
    int data_client = get_data_client(_socket_info, sd);
    char buffer[1024];
    int read_size = 0;

    custom_write(sd, "150 File status okay; about to open data connection.\n");
    if (fork() == 0) {
        if (data_client == -1) {
            data_client = accept(data_socket,
        (struct sockaddr*) &_socket_info->address, &_socket_info->addrlen);
        }
        while ((read_size = read(data_client, buffer, 1024)) > 0) {
            write(1, buffer, read_size);
            write(fd, buffer, read_size);
        }
        clean_data(fd, sd, _socket_info);
        custom_write(sd, "226 Closing data connection. \
    Requested file action successful.\n");
    }
}

void stor_engine(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;
    char *current_directory =
        _socket_info->client_socket[sd_idx]->current_directory;
    int file_fd = 0;
    char *path = NULL;

    if (check_error(sd, _socket_info, arg) == -1)
        return;
    path = create_path(current_directory, arg);
    file_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC);
    write_data(sd, _socket_info, file_fd);
}
