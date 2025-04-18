/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** QUIT Command
*/

#include <stdlib.h>

#include "client.h"
#include "commands.h"
#include "server.h"
#include "game.h"

/**
 * @brief Check if the game can start based on the number of ready clients.
 *
 * This function checks if the game can start based on the number of
 * ready clients and sends the START command if conditions are met.
 *
 * @param server The server structure containing client information.
 */
static void check_game_start(server_t *server)
{
    size_t count = 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd != -1 &&
            server->clients[i].player && server->clients[i].player->ready) {
            count++;
        }
    }
    if (count == server->next_id - 1 && count > 1) {
        server->game->game_state = GAME_IN_PROGRESS;
        start_command(server);
        if (server->debug)
            printf("Game started with %ld players\n", count);
    }
}

/**
 * @brief Handle the READY command.
 *
 * This function handles the READY command from the client and updates
 * the client's state accordingly.
 *
 * @param command The command structure containing the command name and
 * arguments.
 * @param client The client structure associated with the command.
 * @return command_status_t The status of the command execution.
 */
command_status_t ready_command(command_t *command, client_t *client)
{
    (void)command;
    if (client->handshake != HANDSHAKE_DONE ||
        client->server->game->game_state != GAME_START ||
        client->player == NULL) {
        dprintf(client->client_sockfd, "ERROR Not accepting ready now\r\n");
        return COMMAND_FAILURE;
    }
    if (client->player != NULL && client->player->ready) {
        dprintf(client->client_sockfd, "ERROR Already ready\r\n");
        return COMMAND_FAILURE;
    }
    client->player->ready = true;
    dprintf(client->client_sockfd, "OK\r\n");
    if (client->server->debug)
        printf("Client %ld is ready\n", client->id);
    check_game_start(client->server);
    return COMMAND_SUCCESS;
}
