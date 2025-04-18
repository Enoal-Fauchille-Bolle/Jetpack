/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Command Executor
*/

#include <string.h>

#include "client.h"
#include "commands.h"
#include "server.h"
#include "utils.h"

const command_handler_t command_handlers[] = {
    {"QUIT", quit_command}, {"READY", ready_command}, {NULL, NULL}};

/**
 * @brief Get the command handler for a given command.
 *
 * This function searches for the command handler corresponding to the
 * provided command name in the command_handlers array.
 *
 * @param command The command structure containing the command name.
 * @return command_handler_t The handler for the specified command.
 */
static command_handler_t get_command_handler(command_t *command)
{
    touppercase(command->name);
    for (int i = 0; command_handlers[i].command_name; i++) {
        if (strcmp(command_handlers[i].command_name, command->name) == 0) {
            return command_handlers[i];
        }
    }
    return (command_handler_t){NULL, NULL};
}

/**
 * @brief Execute a command for a client.
 *
 * This function retrieves the appropriate command handler based on the
 * command name and executes it, passing the command and client as
 * arguments.
 *
 * @param command The command structure containing the command name and
 * arguments.
 * @param client The client structure associated with the command.
 * @return command_status_t The status of the command execution.
 */
command_status_t execute_command(command_t *command, client_t *client)
{
    command_handler_t handler = {0};

    if (!command) {
        if (client->server->debug)
            printf("Invalid command: NULL\n");
        dprintf(client->client_sockfd, "COMMAND NOT FOUND\r\n");
        return COMMAND_NOT_FOUND;
    }
    handler = get_command_handler(command);
    if (!handler.handler) {
        if (client->server->debug)
            printf("Invalid command: %s\n", command->name);
        dprintf(client->client_sockfd, "COMMAND NOT FOUND\r\n");
        return COMMAND_NOT_FOUND;
    }
    return handler.handler(command, client);
}
