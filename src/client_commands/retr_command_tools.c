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
        exit(84);
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

void retr_engine(int sd, socket_info_s *_socket_info, char *arg)
{
    char *filecontent = NULL;
    int data_socket = get_data_socket(_socket_info, sd);
    int data_client = get_data_client(_socket_info, sd);

    if (data_socket == -1 || data_client == -1) {
        custom_write(sd, "xxx Error (RFC compliant)\n");
        return;
    }
    if (arg == NULL) {
        custom_write(sd, "xxx Error (RFC compliant)\n");
        return;
    }

    filecontent = open_file(arg);
    send_data(sd, _socket_info, filecontent);
}
