/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** QUIT Command
*/

#include "client.h"
#include "commands.h"

/**
 * @brief Handle the QUIT command.
 *
 * This function handles the QUIT command from the client and closes
 * the connection.
 *
 * @param command The command structure containing the command name and
 * arguments.
 * @param client The client structure associated with the command.
 * @return command_status_t The status of the command execution.
 */
command_status_t quit_command(command_t *command, client_t *client)
{
    (void)command;
    (void)client;
    return COMMAND_QUIT;
}
