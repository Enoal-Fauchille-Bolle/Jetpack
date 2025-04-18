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
