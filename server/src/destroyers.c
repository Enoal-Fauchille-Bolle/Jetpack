/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Destroyers File
*/

#include "destroyers.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"
#include "server.h"

/**
 * @brief Destroy the server and free allocated resources.
 *
 * This function closes all client connections, frees the map memory,
 * and closes the server socket.
 *
 * @param server The server structure to destroy.
 * @param fds The array of poll file descriptors.
 * @param client The array of client structures.
 */
void destroy_server(server_t *server, struct pollfd *fds, client_t *client)
{
    for (int i = 1; i < MAX_CLIENTS + 1; i++) {
        if (fds[i].fd >= 0) {
            dprintf(fds[i].fd, "Connection closed by server.\r\n");
            destroy_client(&client[i], true);
            close(fds[i].fd);
        }
    }
    free(server->map);
    close(server->sockfd);
}

/**
 * @brief Destroy a client and free allocated resources.
 *
 * This function closes the client connection and frees the memory
 * associated with the client structure.
 *
 * @param client The client structure to destroy.
 * @param verbose Boolean value indicating whether to print a message.
 */
void destroy_client(client_t *client, bool verbose)
{
    if (client == NULL)
        return;
    if (verbose)
        printf("Disconnected %s:%d\n",
            inet_ntoa(client->client_addr->sin_addr),
            ntohs(client->client_addr->sin_port));
    fclose(client->stream);
}

/**
 * @brief Destroy a command and free allocated resources.
 *
 * This function frees the memory associated with the command structure
 * and its arguments.
 *
 * @param command The command structure to destroy.
 */
void destroy_command(command_t *command)
{
    char **tokens = NULL;

    if (command == NULL)
        return;
    tokens = command->argv - 1;
    free(command->name);
    for (int i = 0; i < command->argc && command->argv[i]; i++) {
        free(command->argv[i]);
    }
    free(tokens);
}
