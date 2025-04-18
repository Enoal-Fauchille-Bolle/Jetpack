/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** handshake Responses Header
*/

#ifndef HANDSHAKE_RESPONSES_H_
    #define HANDSHAKE_RESPONSES_H_

    #include "client.h"

typedef enum handshake_response_status_e {
    HANDSHAKE_RESPONSE_SUCCESS,
    HANDSHAKE_RESPONSE_FAILURE,
    HANDSHAKE_RESPONSE_NOT_FOUND,
    HANDSHAKE_RESPONSE_QUIT,
} handshake_response_status_t;

typedef struct handshake_response_handler_s {
    handshake_state_t handshake_state;
    handshake_response_status_t (*handler)(client_t *client);
} handshake_response_handler_t;

// Handshake Response Executor
handshake_response_status_t execute_handshake_response(client_t *client);

// Handshake Responses
handshake_response_status_t id_handshake_response(client_t *client);
handshake_response_status_t map_handshake_response(client_t *client);
handshake_response_status_t lobby_handshake_response(client_t *client);
handshake_response_status_t start_handshake_response(client_t *client);

#endif /* !HANDSHAKE_RESPONSES_H_ */
