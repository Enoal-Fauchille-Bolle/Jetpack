/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Main Header
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #define MAX_CLIENTS 128

    #include "client.h"
    #include "map.h"


typedef struct game_s game_t;
typedef struct server_s {
    int sockfd;
    client_t clients[MAX_CLIENTS];
    struct sockaddr_in addr;
    int port;
    map_t *map;
    bool debug;
    size_t next_id;
    game_t *game;
} server_t;

#endif /* !SERVER_H_ */
