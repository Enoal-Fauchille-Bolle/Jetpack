/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Collisions Header
*/

#ifndef COLLISIONS_H_
    #define COLLISIONS_H_

    #include <stddef.h>

    #include "server.h"

typedef struct hitbox_s {
    float x_min;
    float x_max;
    float y_min;
    float y_max;
    int col_start;
    int col_end;
    int row_start;
    int row_end;
} hitbox_t;

void check_collisions(server_t *server);

#endif /* !COLLISIONS_H_ */
