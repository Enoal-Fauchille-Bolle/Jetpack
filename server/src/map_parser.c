/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Map Parser
*/

#include "server.h"

static int check_map_height(FILE *file)
{
    char buffer[BUFFER_SIZE];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
        if (count > MAP_MAX_HEIGHT) {
            return -1;
        }
    }
    return count;
}

static void free_resources(map_t *map, FILE *file)
{
    if (map)
        free(map);
    if (file)
        fclose(file);
}

static int verify_map_height(FILE *file, map_t *map)
{
    int height = check_map_height(file);

    if (height == -1) {
        fprintf(stderr,
            "Error: Map height exceeds maximum allowed limit (%d).\n",
            MAP_MAX_HEIGHT);
        free_resources(map, file);
        return 0;
    }
    return 1;
}

static int read_map_lines(FILE *file, map_t *map)
{
    char buffer[BUFFER_SIZE];

    for (int i = 0; fgets(buffer, sizeof(buffer), file) != NULL; i++) {
        map->map[i] = strdup(buffer);
        if (map->map[i] == NULL)
            return 0;
    }
    return 1;
}

map_t *map_parser(char *path)
{
    FILE *file = fopen(path, "r");
    map_t *map = malloc(sizeof(map_t));

    if (file == NULL || map == NULL) {
        free_resources(map, file);
        return NULL;
    }
    if (!verify_map_height(file, map))
        return NULL;
    fseek(file, 0, SEEK_SET);
    if (!read_map_lines(file, map)) {
        free_resources(map, file);
        return NULL;
    }
    map->width = strlen(map->map[0]);
    map->path = strdup(path);
    fclose(file);
    return map;
}
