/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** FLY Command
*/

#include <string.h>

#include "client.h"
#include "commands.h"

command_status_t fly_command(command_t *command, client_t *client)
{
    if (command->argc != 1) {
        dprintf(client->client_sockfd, "ERROR Invalid fly status\r\n");
        return COMMAND_FAILURE;
    }
    if (strcmp(command->argv[0], "1") == 0) {
        client->player->flying = true;
        dprintf(client->client_sockfd, "OK\r\n");
    } else if (strcmp(command->argv[0], "0") == 0) {
        client->player->flying = false;
        dprintf(client->client_sockfd, "OK\r\n");
    } else {
        dprintf(client->client_sockfd, "ERROR Invalid fly status\r\n");
        return COMMAND_FAILURE;
    }
    return COMMAND_SUCCESS;
}
