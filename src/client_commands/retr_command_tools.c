/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** retr_command_tools
*/

#include "server.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "client_handling.h"

char *open_file(char *filepath)
{
    struct stat size;
    char *filecontent;
    int open_file = open(filepath, O_RDONLY);

    if (open_file == -1)
        return (NULL);

    stat(filepath, &size);
    filecontent = malloc(sizeof(char) * size.st_size + 1);
    filecontent[0] = '\0';
    read(open_file, filecontent, size.st_size);
    close(open_file);
    return (filecontent);
}

void send_data(int sd, socket_info_s *_socket_info, char *filecontent)
{
    int data_socket = get_data_socket(_socket_info, sd);
    int data_client = get_data_client(_socket_info, sd);

    custom_write(sd, "150 File status okay; about to open data connection.\n");
    write(data_client, filecontent, strlen(filecontent));
    free(filecontent);
    close(data_client);
    close(data_socket);
    remove_data(_socket_info, sd);

    custom_write(sd, "226 Closing data connection. \
Requested file action successful.\n");
}

int check_error(int sd, socket_info_s *_socket_info, char *arg)
{
    int data_socket = get_data_socket(_socket_info, sd);
    int data_client = get_data_client(_socket_info, sd);
    char *nextparam = strtok(NULL, " ");

    if (data_socket == -1 || data_client == -1) {
        custom_write(sd, "425 Can't open data connection\n");
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

void retr_engine(int sd, socket_info_s *_socket_info, char *arg)
{
    char *filecontent = NULL;
    char *path;

    if (check_error(sd, _socket_info, arg) == -1)
        return;
    
    path = malloc(sizeof(char) * strlen(_socket_info->current_directory) + strlen(arg) + 1);
    strcat(path, _socket_info->current_directory);
    strcat(path, arg);
    filecontent = open_file(arg);
    if (filecontent == NULL) {
        custom_write(sd, "550 Requested action not taken. \
File unavailable\n");
        remove_data(_socket_info, sd);
        return;
    }
    send_data(sd, _socket_info, filecontent);
}
