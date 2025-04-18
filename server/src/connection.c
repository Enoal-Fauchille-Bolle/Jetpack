/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Connection File
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "server.h"
#include "connection.h"
#include "destroyers.h"

/**
 * @brief Initialize a client structure.
 *
 * This function initializes a client structure with the provided server,
 * socket file descriptor, and client address.
 *
 * @param server The server structure.
 * @param client_sockfd The socket file descriptor for the client.
 * @param client_addr The address of the client.
 * @return client_t The initialized client structure.
 */
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

/**
 * @brief Initialize the poll file descriptors.
 *
 * This function initializes the poll file descriptors for the server
 * socket and client sockets.
 *
 * @param fds The array of poll file descriptors.
 * @param server_sockfd The socket file descriptor for the server.
 */
static void init_poll_fds(struct pollfd *fds, int server_sockfd)
{
    for (int i = 0; i < MAX_CLIENTS + 1; i++) {
        fds[i].fd = -1;
    }
    fds[0].fd = server_sockfd;
    fds[0].events = POLLIN;
}

/**
 * @brief Accept a new client connection.
 *
 * This function accepts a new client connection and initializes the
 * client structure.
 *
 * @param server The server structure.
 * @param clients The array of client structures.
 * @param fds The array of poll file descriptors.
 * @param max_fds The maximum number of file descriptors.
 */
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

/**
 * @brief Handle client connection events.
 *
 * This function processes the events for each client connection and
 * handles the connection accordingly.
 *
 * @param fds The array of poll file descriptors.
 * @param max_fds The maximum number of file descriptors.
 * @param clients The array of client structures.
 */
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

/**
 * @brief Process the connection events.
 *
 * This function processes the connection events for the server and
 * handles new connections and client events.
 *
 * @param server The server structure.
 * @param fds The array of poll file descriptors.
 * @param clients The array of client structures.
 * @return int 0 on success, 1 on error.
 */
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

/**
 * @brief Process the connections for the server.
 *
 * This function initializes the poll file descriptors and processes
 * the connections for the server.
 *
 * @param server The server structure.
 * @return int 0 on success, 1 on error.
 */
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
