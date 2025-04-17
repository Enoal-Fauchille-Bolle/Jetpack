/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Connection File
*/

#include <errno.h>

#include "server.h"

static client_t init_client(
    server_t *server, int client_sockfd, struct sockaddr_in *client_addr)
{
    client_t client = {0};

    client.server = server;
    client.client_sockfd = client_sockfd;
    client.client_addr = malloc(sizeof(struct sockaddr_in));
    if (client.client_addr != NULL)
        memcpy(client.client_addr, client_addr, sizeof(struct sockaddr_in));
    client.stream = fdopen(client_sockfd, "r");
    if (client.stream == NULL) {
        perror("fdopen");
        close(client_sockfd);
        return (client_t){0};
    }
    client.id = server->next_id;
    server->next_id++;
    client.handshake = HANDSHAKE_START;
    client.handshake = WAITING_FOR_ID_OK;
    dprintf(client.client_sockfd, "ID %ld\r\n", client.id);
    return client;
}

static void init_poll_fds(struct pollfd *fds, int server_sockfd)
{
    for (int i = 0; i < MAX_CLIENTS + 1; i++) {
        fds[i].fd = -1;
    }
    fds[0].fd = server_sockfd;
    fds[0].events = POLLIN;
}

static void accept_new_connection(
    server_t *server, client_t *clients, struct pollfd *fds, int max_fds)
{
    struct sockaddr_in client_addr = {0};
    socklen_t client_addr_len = sizeof(client_addr);
    int client_sockfd = accept(
        server->sockfd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_sockfd == -1)
        return perror("accept");
    if (server->debug)
        printf("Connection from %s:%d: ID %ld\n",
            inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port),
            server->next_id);
    for (int i = 1; i < max_fds; i++) {
        if (fds[i].fd < 0) {
            clients[i] = init_client(server, client_sockfd, &client_addr);
            fds[i].fd = client_sockfd;
            fds[i].events = POLLIN;
            break;
        }
    }
}

static void process_client_events(
    struct pollfd *fds, int max_fds, client_t *clients)
{
    for (int i = 1; i < max_fds; i++) {
        if (fds[i].fd < 0)
            continue;
        if (fds[i].revents & POLLIN) {
            handle_connection(&fds[i], &clients[i]);
        }
    }
}

static int process_connection(
    server_t *server, struct pollfd *fds, client_t *clients)
{
    int result = poll(fds, MAX_CLIENTS + 1, POLL_TIMEOUT);

    if (result < 0) {
        if (errno != EINTR)
            perror("poll");
        return 1;
    }
    if (fds[0].revents & POLLIN && server->game_state == GAME_START) {
        accept_new_connection(server, clients, fds, MAX_CLIENTS + 1);
    }
    process_client_events(fds, MAX_CLIENTS + 1, clients);
    return 0;
}

int process_connections(server_t *server)
{
    struct pollfd fds[MAX_CLIENTS + 1];

    init_poll_fds(fds, server->sockfd);
    server->next_id = 1;
    while (true) {
        if (process_connection(server, fds, server->clients))
            break;
    }
    destroy_server(server, fds, server->clients);
    return 0;
}
