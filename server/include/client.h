/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Client Header
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <netinet/in.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <sys/socket.h>

    #include "player.h"

typedef enum {
    HANDSHAKE_START,
    WAITING_FOR_ID_OK,
    WAITING_FOR_MAP_OK,
    WAITING_FOR_LOBBY_OK,
    WAITING_FOR_START_OK,
    WAITING_FOR_PLAYER_OK,
    HANDSHAKE_DONE
} handshake_state_t;

typedef struct server_s server_t;

typedef struct client_s {
    size_t id;
    server_t *server;
    int client_sockfd;
    struct sockaddr_in *client_addr;
    FILE *stream;
    handshake_state_t handshake;
    player_t *player;
} client_t;

#endif /* !CLIENT_H_ */
