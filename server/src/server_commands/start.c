/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** START Command
*/

#include <string.h>

#include "server.h"
#include "game.h"
#include "commands.h"

/**
 * @brief Send the start command to all clients.
 *
 * This function sends the START command to all clients in the server.
 *
 * @param server The server structure containing client information.
 */
command_status_t start_command(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd != -1) {
            server->clients[i].handshake = WAITING_FOR_START_OK;
            dprintf(server->clients[i].client_sockfd, "START\r\n");
        }
    }
    return COMMAND_SUCCESS;
}
