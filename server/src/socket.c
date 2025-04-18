/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Socket File
*/

#include <stdlib.h>

#include "server.h"
#include "connection.h"

static int listen_socket(int server_sockfd)
{
    if (listen(server_sockfd, MAX_CLIENTS) == -1) {
        perror("listen");
        return -1;
    }
    return 0;
}

static int bind_socket(int server_sockfd, struct sockaddr_in *server_addr)
{
    socklen_t addr_len = sizeof(*server_addr);

    if (bind(server_sockfd, (struct sockaddr *)server_addr, addr_len) == -1) {
        perror("bind");
        return -1;
    }
    return 0;
}

static struct sockaddr_in init_sockin(int port)
{
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    return server_addr;
}

static int setup_socket_fd(void)
{
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_sockfd == -1) {
        perror("socket");
    }
    return server_sockfd;
}

static int set_final_port(int server_sockfd)
{
    struct sockaddr_in server_addr = {0};
    socklen_t addr_len = sizeof(server_addr);

    getsockname(server_sockfd, (struct sockaddr *)&server_addr, &addr_len);
    return ntohs(server_addr.sin_port);
}

static bool init_server(server_t *server, int port)
{
    server->sockfd = setup_socket_fd();
    if (server->sockfd == -1)
        return false;
    server->addr = init_sockin(port);
    if (bind_socket(server->sockfd, &server->addr) == -1)
        return false;
    server->port = set_final_port(server->sockfd);
    return (listen_socket(server->sockfd) != -1);
}

static void init_clients(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i].client_sockfd = -1;
        server->clients[i].server = NULL;
        server->clients[i].client_addr = NULL;
        server->clients[i].handshake = HANDSHAKE_DONE;
        server->clients[i].ready = false;
        server->clients[i].flying = false;
    }
}

server_t *setup_socket(int port, bool debug)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server || !init_server(server, port)) {
        free(server);
        return NULL;
    }
    init_clients(server);
    server->map = NULL;
    server->debug = debug;
    server->next_id = 1;
    server->game_state = GAME_START;
    return server;
}
