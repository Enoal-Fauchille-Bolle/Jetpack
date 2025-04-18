/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Command Executor
*/

#include <string.h>

#include "server.h"
#include "client.h"
#include "commands.h"
#include "utils.h"

const command_handler_t command_handlers[] = {
    {"QUIT", quit_command}, {"READY", ready_command}, {NULL, NULL}};

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
