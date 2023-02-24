/*
** EPITECH PROJECT, 2023
** MIRROR-B-NWP-400-NAN-4-1-myftp-andreas.le-tanter [WSL : Ubuntu]
** File description:
** function_pointer
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>

const char *COMMAND_NAME[] = {
    "USER", "PASS", "CWD", "CDUP", "QUIT", "DELE",
        "PWD", "PASV", "PORT", "HELP", "NOOP", 0
};

void handleUSERCommand()
{
    write(1, "USER command\n", strlen("USER command\n"));
}

void handlePASSCommand()
{
    write(1, "PASS command\n", strlen("PASS command\n"));
}

void handleCWDCommand()
{
    write(1, "CWD command\n", strlen("CWD command\n"));
}

void handleCDUPCommand()
{
    write(1, "CDUP command\n", strlen("CDUP command\n"));
}

void handleQUITCommand()
{
    write(1, "QUIT command\n", strlen("QUIT command\n"));
}

void handleDELECommand()
{
    write(1, "DELE command\n", strlen("DELE command\n"));
}

void handlePWDCommand()
{
    write(1, "PWD command\n", strlen("PWD command\n"));
}

void handlePASVCommand()
{
    write(1, "PASV command\n", strlen("PASV command\n"));
}

void handlePORTCommand()
{
    write(1, "PORT command\n", strlen("PORT command\n"));
}

void handleHELPCommand()
{
    write(1, "HELP command\n", strlen("HELP command\n"));
}

void handleNOOPCommand()
{
    write(1, "NOOP command\n", strlen("NOOP command\n"));
}

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
    handleNOOPCommand
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
