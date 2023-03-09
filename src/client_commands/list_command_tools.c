/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** list_command_tools
*/

#include <string.h>
#include <unistd.h>
#include "server.h"
#include "client_commands.h"
#include "client_handling.h"
#include <sys/wait.h>

static int check_error(int sd, socket_info_s *_socket_info, char *arg)
{
    int data_socket = get_data_socket(_socket_info, sd);
    int data_client = get_data_client(_socket_info, sd);

    if (data_socket == -1) {
        custom_write(sd, "503 Bad sequence of commands\n");
        return -1;
    }
    if (data_client == -1) {
        custom_write(sd, "425 Can't open data connection\n");
        return -1;
    }
    return 0;
}

static int handle_execve(int sd, int data_sd, char **args)
{
    int child_pid = 0;
    int child_status = 0;

    child_pid = fork();
    if (child_pid == 0) {
        dup2(data_sd, 1);
        execve("/bin/ls", args, NULL);
    } else {
        waitpid(child_pid, &child_status, 0);
        if (WEXITSTATUS(child_status) != 0)  {
            custom_write(sd, "550 Requested action not taken.\n");
            return (-1);
        }
    }
    return (0);
}

void list_engine(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;
    int data_sd = _socket_info->client_socket[sd_idx]->data_client;

    char *args[4] = {"/bin/ls", "-l", arg, NULL};

    if (check_error(sd, _socket_info, arg) == -1)
        return;
    custom_write(sd, "125 Data connection already open; transfer starting.\n");
    if (handle_execve(sd, data_sd, args) == -1)
        return;
    custom_write(sd, "226 Closing data connection.\n");
    close(data_sd);
}
