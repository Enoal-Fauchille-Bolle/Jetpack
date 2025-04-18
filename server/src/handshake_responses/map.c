/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** MAP Handshake Response
*/

#include <stdlib.h>

#include "client.h"
#include "handshake_responses.h"
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
 * @brief Send the lobby information to the client.
 *
 * This function sends the lobby information, including client IDs and
 * ready client IDs, to the specified client socket.
 *
 * @param client The client structure.
 * @param clientfd The socket file descriptor of the client.
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
 * @brief Handle the lobby handshake response from the client.
 *
 * This function processes the lobby handshake response from the client
 * and sends the lobby information to all clients.
 *
 * @param client The client structure associated with the handshake response.
 * @return handshake_response_status_t The status of the handshake response.
 */
handshake_response_status_t map_handshake_response(client_t *client)
{
    size_t *client_indexes = get_client_ids(client->server);
    size_t *ready_client_indexes = get_ready_client_ids(client->server);

    if (!client_indexes)
        return COMMAND_FAILURE;
    client->handshake = WAITING_FOR_LOBBY_OK;
    dprintf(client->client_sockfd, "LOBBY ");
    display_lobby_ids(
        client->client_sockfd, client_indexes, ready_client_indexes);
    free(client_indexes);
    free(ready_client_indexes);
    return COMMAND_SUCCESS;
}
