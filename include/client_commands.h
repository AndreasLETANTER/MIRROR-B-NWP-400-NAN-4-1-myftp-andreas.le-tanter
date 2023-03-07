/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** client_command
*/

#pragma once
#include <stdbool.h>

int seekcommand(char *userInput, int sd, socket_info_s *_socket_info);
void handle_user_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_pass_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_quit_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_cwd_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_cdup_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_pwd_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_dele_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_list_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_retr_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_stor_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_cwd_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_cdup_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_pwd_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_dele_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_list_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_retr_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_stor_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_noop_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_help_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_pasv_command(int sd, socket_info_s *_socket_info, char *arg);
void handle_port_command(int sd, socket_info_s *_socket_info, char *arg);

void retr_engine(int sd, socket_info_s *_socket_info, char *arg);
void quit_engine(int sd_idx, socket_info_s *_socket_info, char *arg);
bool is_logged(int sd_idx, socket_info_s *_socket_info);
void list_engine(int sd_idx, socket_info_s *_socket_info, char *arg);
