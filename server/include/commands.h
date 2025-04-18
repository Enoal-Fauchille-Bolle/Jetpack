/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Commands Header
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "client.h"

typedef struct command_s {
    char *name;
    int argc;
    char **argv;
} command_t;

typedef enum command_status_e {
    COMMAND_SUCCESS,
    COMMAND_FAILURE,
    COMMAND_NOT_FOUND,
    COMMAND_QUIT,
} command_status_t;

typedef struct command_handler_s {
    char *command_name;
    command_status_t (*handler)(command_t *command, client_t *client);
} command_handler_t;

// Command Parser
command_t *parse_buffer(char *buffer);

// Command Executor
command_status_t execute_command(command_t *command, client_t *client);

// Handshake Response Executor
command_status_t execute_handshake_response(client_t *client);

// Commands
command_status_t quit_command(command_t *command, client_t *client);
command_status_t ready_command(command_t *command, client_t *client);

#endif /* !COMMANDS_H_ */
