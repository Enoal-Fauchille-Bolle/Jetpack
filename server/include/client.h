/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Client Header
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <stdio.h>
    #include <stdbool.h>
    #include <sys/socket.h>
    #include <netinet/in.h>

typedef enum {
    HANDSHAKE_START,
    WAITING_FOR_ID_OK,
    WAITING_FOR_MAP_OK,
    WAITING_FOR_LOBBY_OK,
    WAITING_FOR_START_OK,
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
    bool ready;
    bool flying;
} client_t;

#endif /* !CLIENT_H_ */
