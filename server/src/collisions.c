/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Collisions
*/

#include "collisions.h"

#include <math.h>

#include "commands.h"
#include "game.h"
#include "server.h"

static hitbox_t compute_hitbox(server_t *server, player_t *player)
{
    hitbox_t hb;
    float center_x = server->game->x;
    float center_y = player->y;

    hb.x_min = center_x - 1.0;
    hb.x_max = center_x + 1.0;
    hb.y_min = center_y - 1.0;
    hb.y_max = center_y + 1.0;
    hb.col_start = (int)floor(hb.x_min);
    hb.col_end = (int)ceil(hb.x_max) - 1;
    hb.row_start = (int)floor(hb.y_min);
    hb.row_end = (int)ceil(hb.y_max) - 1;
    if (hb.row_start < 0)
        hb.row_start = 0;
    if (hb.col_end >= (int)server->map->width)
        hb.col_end = (int)server->map->width - 1;
    if (hb.row_end >= MAP_MAX_HEIGHT)
        hb.row_end = MAP_MAX_HEIGHT - 1;
    return hb;
}

static int is_point_in_hitbox(int r, int c, hitbox_t hb)
{
    return (hb.x_min < (c + 1) && hb.x_max > c && hb.y_min < (r + 1) &&
            hb.y_max > r);
}

static int handle_obstacle_collision(
    server_t *server, player_t *player, int r, int c)
{
    if (server->map->map[r][c] == 'e') {
        player->alive = false;
        player->death_x_pos = server->game->x;
        return 1;
    }
    return 0;
}

static void handle_coin_collision(
    server_t *server, player_t *player, int r, int c)
{
    if (server->map->map[r][c] == 'c') {
        player->score++;
        server->map->map[r][c] = ' ';
    }
}

static int check_obstacle_collision(
    server_t *server, player_t *player, hitbox_t hb)
{
    int c = hb.col_start;

    for (int r = hb.row_start; r <= hb.row_end;) {
        if (c > hb.col_end) {
            r++;
            c = hb.col_start;
            continue;
        }
        if (is_point_in_hitbox(r, c, hb) &&
            handle_obstacle_collision(server, player, r, c))
            return 1;
        c++;
    }
    return 0;
}

static void process_coin_collision(
    server_t *server, player_t *player, hitbox_t hb)
{
    int c = hb.col_start;

    for (int r = hb.row_start; r <= hb.row_end;) {
        if (c > hb.col_end) {
            r++;
            c = hb.col_start;
            continue;
        }
        if (is_point_in_hitbox(r, c, hb))
            handle_coin_collision(server, player, r, c);
        c++;
    }
}

static void check_player_collision(server_t *server, player_t *player)
{
    hitbox_t hb = compute_hitbox(server, player);

    if (check_obstacle_collision(server, player, hb))
        return;
    process_coin_collision(server, player, hb);
}

void check_collisions(server_t *server)
{
    client_t *client;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        client = &server->clients[i];
        if (client->client_sockfd == -1 || !client->player)
            continue;
        check_player_collision(server, client->player);
    }
}
