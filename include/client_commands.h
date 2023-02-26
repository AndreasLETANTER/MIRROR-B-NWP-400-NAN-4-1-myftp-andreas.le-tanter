/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** client_command
*/

#pragma once

int seekCommand(char *userInput, int sd, socket_info_s *_socket_info);
void handleUSERCommand();
void handlePASSCommand();
void handleQUITCommand();
void handleCWDCommand();
void handleCDUPCommand();
void handlePWDCommand();
void handleDELECommand();
void handleLISTCommand();
void handleRETRCommand();
void handleSTORCommand();
void handleCWDCommand();
void handleCDUPCommand();
void handlePWDCommand();
void handleDELECommand();
void handleLISTCommand();
void handleRETRCommand();
void handleSTORCommand();
void handleNOOPCommand();
void handleHELPCommand();
void handlePASVCommand(int sd, socket_info_s *_socket_info);
void handlePORTCommand();
