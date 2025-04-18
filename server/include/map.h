/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Map Header
*/

#ifndef MAP_H_
    #define MAP_H_

    #define BUFFER_SIZE 1024
    #define MAP_MAX_HEIGHT 10

    #include <stddef.h>

typedef struct map_s {
    char *path;
    size_t width;
    char *map[10];
} map_t;

map_t *map_parser(char *path);

#endif /* !MAP_H_ */
