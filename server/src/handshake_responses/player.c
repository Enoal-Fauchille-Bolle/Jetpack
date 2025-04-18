/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** PLAYER Handshake Response
*/

#include "client.h"
#include "handshake_responses.h"

/**
 * @brief Handle the PLAYER handshake response.
 *
 * This function processes the PLAYER handshake response from the client.
 *
 * @param client The client structure.
 * @return handshake_response_status_t The status of the handshake response.
 */
handshake_response_status_t player_handshake_response(client_t *client)
{
    (void)client;
    return HANDSHAKE_RESPONSE_SUCCESS;
}
