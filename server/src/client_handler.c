/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Client Handler File
*/

#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"
#include "destroyers.h"
#include "handshake_responses.h"

/**
 * @brief Read a line from the socket stream.
 *
 * This function reads a line from the socket stream associated with the
 * client and returns it as a string. The caller is responsible for freeing
 * the allocated memory.
 *
 * @param client The client structure containing the socket stream.
 * @return char* The read line, or NULL on error.
 */
static char *read_socket(client_t *client)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    read = getline(&line, &len, client->stream);
    if (read == -1) {
        free(line);
        return NULL;
    }
    if (line[read - 1] == '\n')
        line[read - 1] = '\0';
    return line;
}

/**
 * @brief Handle the handshake response from the client.
 *
 * This function processes the handshake response from the client and
 * executes the appropriate action based on the response.
 *
 * @param client The client structure.
 * @param buffer The buffer containing the handshake response.
 * @return command_status_t The status of the handshake response.
 */
static handshake_response_status_t handle_handshake_response(
    client_t *client, char *buffer)
{
    if (strcasecmp(buffer, "OK") != 0 && strcasecmp(buffer, "ERROR") != 0) {
        return HANDSHAKE_RESPONSE_NOT_FOUND;
    }
    if (client->server->debug)
        printf("Handshake response from ID %ld: %s\n", client->id, buffer);
    if (strcasecmp(buffer, "ERROR") == 0) {
        client->handshake = HANDSHAKE_DONE;
        return HANDSHAKE_RESPONSE_NOT_FOUND;
    }
    return execute_handshake_response(client);
}

/**
 * @brief Handle the client command.
 *
 * This function processes the command received from the client and
 * executes it.
 *
 * @param client The client structure.
 * @param buffer The buffer containing the command.
 * @return command_status_t The status of the command execution.
 */
static command_status_t handle_client_command(client_t *client, char *buffer)
{
    command_status_t result = COMMAND_NOT_FOUND;
    command_t *command = NULL;

    if (client->server->debug)
        printf("Command from ID %ld: %s\n", client->id, buffer);
    command = parse_buffer(buffer);
    result = execute_command(command, client);
    destroy_command(command);
    return result;
}

/**
 * @brief Handle the connection for a client.
 *
 * This function processes the connection events for a client and
 * handles the handshake response and client commands.
 *
 * @param fd The poll file descriptor for the client.
 * @param client The client structure.
 */
void handle_connection(struct pollfd *fd, client_t *client)
{
    char *buffer = read_socket(client);
    command_status_t command_result;
    handshake_response_status_t handshake_response_result;

    if (!buffer)
        return;
    handshake_response_result = handle_handshake_response(client, buffer);
    if (handshake_response_result == HANDSHAKE_RESPONSE_NOT_FOUND)
        command_result = handle_client_command(client, buffer);
    if (handshake_response_result == HANDSHAKE_RESPONSE_QUIT ||
        command_result == COMMAND_QUIT) {
        dprintf(fd->fd, "Connection closed by server.\r\n");
        destroy_client(client, true);
        close(fd->fd);
        fd->fd = -1;
    }
    free(buffer);
}
