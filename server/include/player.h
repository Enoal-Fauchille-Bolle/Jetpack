/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Player Header
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include <stddef.h>

    #define PLAYER_SIZE 2

typedef struct player_s {
    bool ready;
    float y;
    int score;
    bool flying;
    bool alive;
    float death_x_pos;
} player_t;

#endif /* !PLAYER_H_ */
