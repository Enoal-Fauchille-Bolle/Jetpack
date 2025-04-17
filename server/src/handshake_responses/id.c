/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** ID Handshake Response
*/

#include "server.h"

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

command_status_t id_handshake_response(client_t *client)
{
    char *raw_map = get_raw_map(client->server->map);

    client->handshake = WAITING_FOR_MAP_OK;
    dprintf(client->client_sockfd, "MAP %ld %s\r\n",
        client->server->map->width, raw_map);
    free(raw_map);
    return COMMAND_SUCCESS;
}
