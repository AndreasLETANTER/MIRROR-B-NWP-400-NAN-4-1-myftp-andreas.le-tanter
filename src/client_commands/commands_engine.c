/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** function_pointer
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "client_commands.h"

const char *COMMAND_NAME[] = {
    "USER", "PASS", "CWD", "CDUP", "QUIT", "DELE",
        "PWD", "PASV", "PORT", "HELP", "NOOP", "RETR", "STOR", "LIST", 0
};

void (*ftpCommands[])() = {
    handleUSERCommand,
    handlePASSCommand,
    handleCWDCommand,
    handleCDUPCommand,
    handleQUITCommand,
    handleDELECommand,
    handlePWDCommand,
    handlePASVCommand,
    handlePORTCommand,
    handleHELPCommand,
    handleNOOPCommand,
    handleRETRCommand,
    handleSTORCommand,
    handleLISTCommand
};

int seekCommand(char *userInput, int sd)
{
    for (int i = 0; COMMAND_NAME[i] != 0; i++) {
        if (strcmp(COMMAND_NAME[i], userInput) == 0) {
            write(sd, "200 Command okay.\n", strlen("200 Command okay.\n"));
            ftpCommands[i]();
            return (0);
        }
    }
    write(sd, "xxx Error (RFC compliant)\n", strlen("xxx Error (RFC compliant)\n"));
    return (84);
}
