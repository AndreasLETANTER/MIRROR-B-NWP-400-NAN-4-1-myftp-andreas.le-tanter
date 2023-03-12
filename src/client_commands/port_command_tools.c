/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** port_command_tools
*/

#include "server.h"
#include "client_handling.h"
#include "client_commands.h"
#include <string.h>
#include <unistd.h>

char *parse_client_adress(char *arg)
{
    char *clientIp = malloc(sizeof(char) * 16);
    int count = 0;
    int idx = 0;

    for (int i = 0; arg[i]; i++) {
        if (arg[i] == ',')
            count++;
    }
    if (count != 5)
        return (NULL);
    for (int nb_coma = 0; arg[idx] && nb_coma != 4; idx++) {
        if (arg[idx] == ',') {
            clientIp[idx] = '.';
            nb_coma++;
        } else {
            clientIp[idx] = arg[idx];
        }
    }
    clientIp[idx - 1] = '\0';
    return (clientIp);
}

int get_nb_after_coma(char *arg, int nb_coma_asked)
{
    int count = 0;
    int idx = 0;
    int idx_nb = 0;
    char *nb_char = malloc(sizeof(char) * 4);

    for (int nb_coma = 0, idx = 0; arg[idx]; idx++) {
        if (arg[idx] == ',')
            nb_coma++;
        if (nb_coma == nb_coma_asked && arg[idx] != ',') {
            nb_char[idx_nb] = arg[idx];
            idx_nb++;
        }
    }
    nb_char[idx_nb] = '\0';
    idx_nb = atoi(nb_char);
    free(nb_char);
    return (idx_nb);
}

int parse_port(char *arg)
{
    int count = 0;
    int idx_nb1 = 0;
    int idx_nb2 = 0;
    int port;
    int nb1 = 0;
    int nb2 = 0;

    for (int i = 0; arg[i]; i++) {
        if (arg[i] == ',')
            count++;
    }
    if (count != 5)
        return (-1);
    nb1 = get_nb_after_coma(arg, 4);
    nb2 = get_nb_after_coma(arg, 5);
    port = nb1 * 256 + nb2;
    return (port);
}

int bind_data_socket_port(int sd, int data_sd, char *clientAdress, int socket)
{
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    inet_pton(AF_INET, clientAdress, &(address.sin_addr));
    address.sin_port = htons(socket);

    if (bind(data_sd,
        (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("bind failed\n");
        exit(84);
    }
    socklen_t len = sizeof(address);
    getsockname(data_sd, (struct sockaddr *) &address, &len);
    custom_write(sd, "200 Command okay.\n");
    listen(data_sd, 1);
    return (data_sd);
}

void handle_port_command(int sd_idx, socket_info_s *_socket_info, char *arg)
{
    int sd = _socket_info->client_socket[sd_idx]->socket_fd;
    char *clientIp = NULL;
    int port = -1;
    int data_sd = create_socket();
    char *next_arg = strtok(NULL, " ");

    if (arg == NULL) {
        custom_write(sd, "504 Command not implemented for that parameter.\n");
        return;
    }
    port = parse_port(arg);
    clientIp = parse_client_adress(arg);
    if (port == -1 || next_arg != NULL || clientIp == NULL) {
        custom_write(sd, "504 Command not implemented for that parameter.\n");
        return;
    }
    data_sd = bind_data_socket_port(sd, data_sd, clientIp, port);
    free(clientIp);
}
