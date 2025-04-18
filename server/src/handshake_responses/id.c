/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** ID Handshake Response
*/

#include <stdlib.h>

#include "handshake_responses.h"
#include "map.h"
#include "server.h"

/**
 * @brief Get a line from the raw map and store it in the raw_map buffer.
 *
 * This function retrieves a line from the map and stores it in the raw_map
 * buffer, updating the position accordingly.
 *
 * @param raw_map The buffer to store the raw map line.
 * @param map The map structure containing the map data.
 * @param row The row index of the map to retrieve.
 * @param pos Pointer to the current position in the raw_map buffer.
 */
static void get_raw_map_line(char *raw_map, map_t *map, int row, int *pos)
{
    char *line = map->map[row];

    if (!line)
        return;
    for (const char *p = line; *p; p++) {
        if (*p != '\n') {
            raw_map[*pos] = *p;
            (*pos)++;
        }
    }
}

/**
 * @brief Get the raw map as a string.
 *
 * This function retrieves the entire map as a single string, with each
 * line concatenated together.
 *
 * @param map The map structure containing the map data.
 * @return char* Pointer to the raw map string, or NULL on error.
 */
static char *get_raw_map(map_t *map)
{
    int raw_map_size = map->width * MAP_MAX_HEIGHT + 1;
    char *raw_map = malloc(raw_map_size * sizeof(char));
    int pos = 0;

    if (!raw_map)
        return NULL;
    for (int row = 0; row < MAP_MAX_HEIGHT; row++) {
        get_raw_map_line(raw_map, map, row, &pos);
    }
    raw_map[pos] = '\0';
    return raw_map;
}

/**
 * @brief Handle the ID handshake response from the client.
 *
 * This function processes the ID handshake response from the client and
 * sends the map information back to the client.
 *
 * @param client The client structure associated with the handshake response.
 * @return handshake_response_status_t The status of the handshake response.
 */
handshake_response_status_t id_handshake_response(client_t *client)
{
    char *raw_map = get_raw_map(client->server->map);

    client->handshake = WAITING_FOR_MAP_OK;
    dprintf(client->client_sockfd, "MAP %ld %s\r\n",
        client->server->map->width, raw_map);
    free(raw_map);
    return HANDSHAKE_RESPONSE_SUCCESS;
}
