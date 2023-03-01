/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** client_handling
*/

#include "server.h"
#include "client_connection.h"

char *getclientadress(int sd)
{
    struct sockaddr_in address;
    char *clientIp;
    int res;

    socklen_t address_size = sizeof(struct sockaddr_in);
    res = getpeername(sd, (struct sockaddr *)&address, &address_size);
    clientIp = strdup(inet_ntoa(address.sin_addr));

    return (clientIp);
}

void handle_client_socket(socket_info_s *_socket_info, fd_set rfds)
{
    int valread = 0;
    char buffer[1024] = { 0 };

    for (int i = 0, sd = 0; i < 1024; i++) {
        sd = _socket_info->client_socket[i]->socket_fd;

        if (_socket_info->client_socket[i]->socket_type == CLIENTSOCKET  && FD_ISSET(sd, &rfds)) {
            valread = read(sd, buffer, 1024);

            check_client_deconnection(sd, valread, _socket_info, i);
            check_client_interaction(buffer, valread, sd, _socket_info);
        }
    }
}

void remove_data(socket_info_s *_socket_info, int sd)
{
    for (int i = 0; i < 1024; i++) {
        if (_socket_info->client_socket[i]->socket_fd == sd) {
            _socket_info->client_socket[i]->socket_fd = -1;
            _socket_info->client_socket[i]->socket_type = -1;
            break;
        }
    }
}

int get_data_socket(socket_info_s *_socket_info, int sd)
{
    for (int i = 0; i < 1024; i++) {
        if (_socket_info->client_socket[i]->socket_fd == sd) {
            return (_socket_info->client_socket[i]->data_socket);
        }
    }
    return (-1);
}

int get_data_client(socket_info_s *_socket_info, int sd)
{
    for (int i = 0; i < 1024; i++) {
        if (_socket_info->client_socket[i]->socket_fd == sd) {
            return (_socket_info->client_socket[i]->data_client);
        }
    }
    return (-1);
}
