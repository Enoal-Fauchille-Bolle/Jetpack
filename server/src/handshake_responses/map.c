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
    (void)client;
    return HANDSHAKE_RESPONSE_SUCCESS;
}
