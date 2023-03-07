/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** client_connection
*/

#include "server_connection.h"
#include "client_handling.h"
#include "client_commands.h"
#include "initialyze_client.h"
#include <stdbool.h>

bool check_client_deconnection(int sd, int valread,
    socket_info_s *_socket_info, int i)
{
    if (valread == 0) {
        close(sd);
        reset_client(_socket_info, i, 0);
        free(_socket_info->client_socket[i]->current_directory);
        return (true);
    }
    return (false);
}

char *remove_non_printable(char *buffer)
{
    for (int i = strlen(buffer); i >= 0; i--) {
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            break;
        } else {
            buffer[i] = '\0';
        }
    }
    return (buffer);
}

void check_client_interaction(char *buffer, int valread, int sd_idx,
    socket_info_s *_socket_info)
{
    if (check_client_deconnection(_socket_info->client_socket[sd_idx]->
        socket_fd, valread, _socket_info, sd_idx) == true)
        return;
    
    buffer = remove_non_printable(buffer);
    seekcommand(buffer, sd_idx, _socket_info);
}
