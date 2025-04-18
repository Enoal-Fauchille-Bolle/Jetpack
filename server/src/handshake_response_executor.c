/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Command Executor
*/

#include "client.h"
#include "server.h"
#include "handshake_responses.h"

const handshake_response_handler_t handshake_response_handlers[] = {
    {WAITING_FOR_ID_OK, id_handshake_response},
    {WAITING_FOR_MAP_OK, map_handshake_response},
    {WAITING_FOR_LOBBY_OK, lobby_handshake_response},
    {WAITING_FOR_START_OK, start_handshake_response}, {HANDSHAKE_DONE, NULL}};

static handshake_response_handler_t get_handshake_response_handler(
    client_t *client)
{
    for (int i = 0;
        handshake_response_handlers[i].handshake_state != HANDSHAKE_DONE;
        i++) {
        if (handshake_response_handlers[i].handshake_state ==
            client->handshake) {
            return handshake_response_handlers[i];
        }
    }
    return (handshake_response_handler_t){HANDSHAKE_DONE, NULL};
}

handshake_response_status_t execute_handshake_response(client_t *client)
{
    handshake_response_handler_t handler = {0};
    handshake_state_t old_state = client->handshake;

    handler = get_handshake_response_handler(client);
    client->handshake = HANDSHAKE_DONE;
    if (!handler.handler) {
        if (client->server->debug && old_state != HANDSHAKE_DONE)
            printf("No Handshake Response Handler for state %d\n",
                client->handshake);
        if (client->server->debug)
            printf("No Handshake\n");
        return COMMAND_FAILURE;
    }
    return handler.handler(client);
}
