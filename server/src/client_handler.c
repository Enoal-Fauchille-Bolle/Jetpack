/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Client Handler File
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

#include "commands.h"
#include "destroyers.h"

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

static command_status_t handle_handshake_response(
    client_t *client, char *buffer)
{
    if (strcasecmp(buffer, "OK") != 0 && strcasecmp(buffer, "ERROR") != 0) {
        return COMMAND_NOT_FOUND;
    }
    if (client->server->debug)
        printf("Handshake response from ID %ld: %s\n", client->id, buffer);
    if (strcasecmp(buffer, "ERROR") == 0) {
        client->handshake = HANDSHAKE_DONE;
        return COMMAND_FAILURE;
    }
    return execute_handshake_response(client);
}

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

void handle_connection(struct pollfd *fd, client_t *client)
{
    char *buffer = read_socket(client);
    command_status_t result;

    if (!buffer)
        return;
    result = handle_handshake_response(client, buffer);
    if (result == COMMAND_NOT_FOUND)
        result = handle_client_command(client, buffer);
    if (result == COMMAND_QUIT) {
        dprintf(fd->fd, "Connection closed by server.\r\n");
        destroy_client(client, true);
        close(fd->fd);
        fd->fd = -1;
    }
    free(buffer);
}
