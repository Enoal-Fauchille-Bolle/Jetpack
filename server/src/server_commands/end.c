/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** END Command
*/

#include <string.h>

#include "server.h"
#include "game.h"
#include "commands.h"

/**
 * @brief Broadcast the end of the game to all clients.
 *
 * This function sends the end of the game message to all clients
 * connected to the server. It includes the client ID that triggered
 * the end of the game.
 *
 * @param server The server structure containing the clients.
 * @param client_id The ID of the client that triggered the end of the game.
 * @return COMMAND_SUCCESS on success, COMMAND_FAILURE on failure.
 */
command_status_t end_command(server_t *server, size_t client_id)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd == -1 ||
            !server->clients[i].player)
            continue;
        dprintf(server->clients[i].client_sockfd,
            "END %lu\r\n", client_id);
    }
    return COMMAND_SUCCESS;
}
