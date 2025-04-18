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

/**
 * @brief Get the IDs of all clients in the server.
 *
 * This function retrieves the IDs of all connected clients in the server
 * and returns them as an array of size_t.
 *
 * @param server The server structure containing client information.
 * @return size_t* Pointer to an array of client IDs, or NULL on error.
 */
static size_t *get_client_ids(server_t *server)
{
    size_t count = 0;
    size_t j = 0;
    size_t *client_indexes = NULL;

    for (int i = 0; i < MAX_CLIENTS; i++)
        if (server->clients[i].client_sockfd != -1)
            count++;
    client_indexes = malloc(sizeof(size_t) * count + 1);
    if (!client_indexes)
        return NULL;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd != -1) {
            client_indexes[j] = i;
            j++;
        }
    }
    client_indexes[j] = 0;
    return client_indexes;
}

/**
 * @brief Get the IDs of all ready clients in the server.
 *
 * This function retrieves the IDs of all ready clients in the server
 * and returns them as an array of size_t.
 *
 * @param server The server structure containing client information.
 * @return size_t* Pointer to an array of ready client IDs, or NULL on error.
 */
static size_t *get_ready_client_ids(server_t *server)
{
    size_t count = 0;
    size_t j = 0;
    size_t *client_indexes = NULL;

    for (int i = 0; i < MAX_CLIENTS; i++)
        if (server->clients[i].client_sockfd != -1)
            count++;
    client_indexes = malloc(sizeof(size_t) * count + 1);
    if (!client_indexes)
        return NULL;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd != -1 &&
            server->clients[i].ready) {
            client_indexes[j] = i;
            j++;
        }
    }
    client_indexes[j] = 0;
    return client_indexes;
}

/**
 * @brief Display the lobby IDs to the client.
 *
 * This function sends the IDs of all clients and ready clients in the
 * lobby to the specified client socket.
 *
 * @param client_sockfd The socket file descriptor of the client.
 * @param client_indexes The array of client IDs.
 * @param ready_client_indexes The array of ready client IDs.
 */
static void display_lobby_ids(
    int client_sockfd, size_t *client_indexes, size_t *ready_client_indexes)
{
    for (int i = 0; client_indexes[i] != 0; i++) {
        dprintf(client_sockfd, "%ld", client_indexes[i]);
        if (client_indexes[i + 1] != 0)
            dprintf(client_sockfd, ",");
    }
    dprintf(client_sockfd, " ");
    for (int i = 0; ready_client_indexes[i] != 0; i++) {
        dprintf(client_sockfd, "%ld", ready_client_indexes[i]);
        if (ready_client_indexes[i + 1] != 0)
            dprintf(client_sockfd, ",");
    }
    dprintf(client_sockfd, "\n");
}

/**
 * @brief Send the lobby information to the client.
 *
 * This function sends the lobby information, including client IDs and
 * ready client IDs, to the specified client socket.
 *
 * @param client The client structure.
 * @param clientfd The socket file descriptor of the client.
 */
static void send_lobby(client_t *client, int clientfd)
{
    size_t *client_indexes = get_client_ids(client->server);
    size_t *ready_client_indexes = get_ready_client_ids(client->server);

    if (!client_indexes)
        return;
    client->handshake = WAITING_FOR_LOBBY_OK;
    dprintf(clientfd, "LOBBY ");
    display_lobby_ids(clientfd, client_indexes, ready_client_indexes);
    free(client_indexes);
    free(ready_client_indexes);
}

/**
 * @brief Send the lobby information to all other clients.
 *
 * This function sends the lobby information to all clients except the
 * specified client.
 *
 * @param client The client structure.
 */
static void send_lobby_to_others(client_t *client)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client->server->clients[i].client_sockfd != -1 &&
            client->server->clients[i].id != client->id) {
            client->server->clients[i].handshake = WAITING_FOR_LOBBY_OK;
            send_lobby(client, client->server->clients[i].client_sockfd);
        }
    }
}

/**
 * @brief Send the start command to all clients.
 *
 * This function sends the START command to all clients in the server.
 *
 * @param server The server structure containing client information.
 */
static void send_start(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd != -1) {
            server->clients[i].handshake = WAITING_FOR_START_OK;
            dprintf(server->clients[i].client_sockfd, "START\r\n");
        }
    }
}

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
            server->clients[i].ready) {
            count++;
        }
    }
    if (count == server->next_id - 1 && count > 1) {
        server->game_state = GAME_IN_PROGRESS;
        send_start(server);
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
    if (client->handshake != HANDSHAKE_DONE) {
        dprintf(client->client_sockfd, "ERROR Not accepting ready now\r\n");
        return COMMAND_FAILURE;
    }
    if (client->server->game_state != GAME_START) {
        dprintf(client->client_sockfd, "ERROR Not accepting ready now\r\n");
        return COMMAND_FAILURE;
    }
    if (client->ready) {
        dprintf(client->client_sockfd, "ERROR Already ready\r\n");
        return COMMAND_FAILURE;
    }
    client->ready = true;
    dprintf(client->client_sockfd, "OK\r\n");
    if (client->server->debug)
        printf("Client %ld is ready\n", client->id);
    send_lobby_to_others(client);
    check_game_start(client->server);
    return COMMAND_SUCCESS;
}
