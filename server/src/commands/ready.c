/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** QUIT Command
*/

#include "server.h"

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

static void send_start(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd != -1) {
            server->clients[i].handshake = WAITING_FOR_START_OK;
            dprintf(server->clients[i].client_sockfd, "START\r\n");
        }
    }
}

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

command_status_t ready_command(command_t *command, client_t *client)
{
    (void)command;
    if (client->handshake != HANDSHAKE_DONE) {
        dprintf(client->client_sockfd, "ERROR: Not accepting ready now\r\n");
        return COMMAND_FAILURE;
    }
    if (client->server->game_state != GAME_START) {
        dprintf(client->client_sockfd, "ERROR: Not accepting ready now\r\n");
        return COMMAND_FAILURE;
    }
    if (client->ready) {
        dprintf(client->client_sockfd, "ERROR: Already ready\r\n");
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
