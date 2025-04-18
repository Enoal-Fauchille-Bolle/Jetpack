/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Map Parser
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "map.h"

/**
 * @brief Check the height of the map in the file.
 *
 * This function reads the map file line by line and counts the number
 * of lines. If the number of lines exceeds MAP_MAX_HEIGHT, it returns -1.
 *
 * @param file The file pointer to the map file.
 * @return int The number of lines in the map, or -1 if it exceeds the limit.
 */
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

/**
 * @brief Free allocated resources.
 *
 * This function frees the allocated memory for the map and closes the
 * file if it is open.
 *
 * @param map The map structure to free.
 * @param file The file pointer to close.
 */
static void free_resources(map_t *map, FILE *file)
{
    if (map)
        free(map);
    if (file)
        fclose(file);
}

/**
 * @brief Verify the height of the map.
 *
 * This function checks if the height of the map exceeds the maximum
 * allowed limit. If it does, it frees the resources and returns 0.
 *
 * @param file The file pointer to the map file.
 * @param map The map structure to verify.
 * @return int 1 if the height is valid, 0 otherwise.
 */
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

/**
 * @brief Read the map lines from the file.
 *
 * This function reads the map lines from the file and stores them in
 * the map structure. It allocates memory for each line and checks for
 * allocation errors.
 *
 * @param file The file pointer to the map file.
 * @param map The map structure to store the lines.
 * @return int 1 on success, 0 on failure.
 */
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

/**
 * @brief Parse the map file and create a map structure.
 *
 * This function opens the map file, verifies its height, reads the
 * lines, and creates a map structure. It returns NULL if any error
 * occurs during the process.
 *
 * @param path The path to the map file.
 * @return map_t* Pointer to the created map structure, or NULL on failure.
 */
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
