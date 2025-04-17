/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** QUIT Command
*/

#include "server.h"

command_status_t quit_command(command_t *command, client_t *client)
{
    (void)command;
    (void)client;
    return COMMAND_QUIT;
}
