/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Game Header
*/

#ifndef GAME_H_
    #define GAME_H_

    #include <stddef.h>

    #include "server.h"

typedef enum {
    GAME_START,
    GAME_IN_PROGRESS,
    GAME_END
} game_state_t;

typedef struct game_s {
    game_state_t game_state;
    size_t tick;
    float x;
} game_t;

void game_tick(server_t *server);

#endif /* !GAME_H_ */
