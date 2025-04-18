/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** PLAYER Command
*/

#include <string.h>

#include "commands.h"
#include "game.h"
#include "server.h"

/**
 * @brief Send player information to a specific client.
 *
 * This function sends the player information to a specific client.
 * It includes the player's ID, X and Y coordinates, score, and flying
 * status.
 *
 * @param server The server structure containing the clients.
 * @param client The client to send the information to.
 */
static void send_players_infos(server_t *server, client_t *client)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd == -1 ||
            !server->clients[i].player)
            continue;
        server->clients[i].handshake = WAITING_FOR_PLAYER_OK;
        if (server->clients[i].player->alive) {
            dprintf(client->client_sockfd, "PLAYER %lu %f %f %d %s\r\n",
                server->clients[i].id, server->game->x,
                server->clients[i].player->y, server->clients[i].player->score,
                server->clients[i].player->flying ? "1" : "0");
        } else {
            dprintf(client->client_sockfd, "PLAYER %lu %f %f %d %s\r\n",
                server->clients[i].id, server->clients[i].player->death_x_pos,
                server->clients[i].player->y, server->clients[i].player->score,
                server->clients[i].player->flying ? "1" : "0");
        }
    }
}

/**
 * @brief Broadcast player information to all clients.
 *
 * This function sends the player information to all clients connected
 * to the server. It includes the player's ID, X and Y coordinates,
 * score, and flying status.
 *
 * @param server The server structure containing the clients.
 */
command_status_t player_command(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd == -1 ||
            !server->clients[i].player)
            continue;
        send_players_infos(server, &server->clients[i]);
    }
    return COMMAND_SUCCESS;
}
