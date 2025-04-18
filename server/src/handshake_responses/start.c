/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** START Handshake Response
*/

#include "client.h"
#include "handshake_responses.h"

/**
 * @brief Handle the START handshake response.
 *
 * This function processes the START handshake response from the client.
 *
 * @param client The client structure.
 * @return handshake_response_status_t The status of the handshake response.
 */
handshake_response_status_t start_handshake_response(client_t *client)
{
    (void)client;
    return COMMAND_SUCCESS;
}
