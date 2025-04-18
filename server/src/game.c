/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Game
*/

#include "game.h"

#include <math.h>

#include "commands.h"
#include "server.h"
#include "collisions.h"

/**
 * @brief Debug function to display player information.
 *
 * This function prints the ID, X and Y coordinates, score, and flying
 * status of each player in the server.
 *
 * @param server The server structure containing the clients.
 */
static void debug_players(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd != -1 &&
            server->clients[i].player) {
            printf("ID %lu: X: %f, Y: %f, Score: %d, Flying: %s, Alive: %s\n",
                server->clients[i].id, server->game->x,
                server->clients[i].player->y, server->clients[i].player->score,
                server->clients[i].player->flying ? "true" : "false",
                server->clients[i].player->alive ? "true" : "false");
        }
    }
}

/**
 * @brief Debug function to display game information.
 *
 * This function prints the current game tick and player information.
 *
 * @param server The server structure containing the game and clients.
 */
static void debug(server_t *server)
{
    printf("Game tick: %lu\n", server->game->tick);
    debug_players(server);
    puts("");
}

/**
 * @brief Update the flying positions of players.
 *
 * This function updates the flying positions of players in the server.
 * If a player is flying, their y-coordinate is increased; otherwise,
 * it is decreased. The y-coordinate is clamped between 0 and 10.
 *
 * @param server The server structure containing the clients.
 */
static void update_fly_positions(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd == -1 ||
            !server->clients[i].player || !server->clients[i].player->alive)
            continue;
        if (server->clients[i].player->flying)
            server->clients[i].player->y += 0.1;
        else
            server->clients[i].player->y -= 0.1;
        if (server->clients[i].player->y < (PLAYER_SIZE / 2))
            server->clients[i].player->y = (PLAYER_SIZE / 2);
        if (server->clients[i].player->y > 10 - (PLAYER_SIZE / 2))
            server->clients[i].player->y = 10 - (PLAYER_SIZE / 2);
    }
}

/**
 * @brief Get the ID of the last alive player.
 *
 * This function checks all clients and returns the ID of the last
 * alive player. If there is only one alive player, their ID is returned;
 * otherwise, 0 is returned.
 *
 * @param server The server structure containing the clients.
 * @return size_t The ID of the last alive player or 0 if none.
 */
static size_t get_alive_player_id(server_t *server)
{
    size_t alive_players = 0;
    size_t alive_player_id = 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd == -1 ||
            !server->clients[i].player)
            continue;
        if (server->clients[i].player->alive) {
            alive_players++;
            alive_player_id = server->clients[i].id;
        }
    }
    if (alive_players == 1)
        return alive_player_id;
    return 0;
}

/**
 * @brief Get the number of alive players.
 *
 * This function counts the number of alive players in the server.
 *
 * @param server The server structure containing the clients.
 * @return size_t The number of alive players.
 */
static size_t get_alive_players(server_t *server)
{
    size_t alive_players = 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].client_sockfd == -1 ||
            !server->clients[i].player)
            continue;
        if (server->clients[i].player->alive) {
            alive_players++;
        }
    }
    return alive_players;
}

/**
 * @brief Check for collisions between players and the map.
 *
 * This function checks for collisions between players and the map.
 * If a player collides with the map, they are marked as not alive.
 *
 * @param server The server structure containing the game and clients.
 */
static void check_end(server_t *server)
{
    if (server->game->x >= server->map->width ||
        get_alive_players(server) == 0) {
        server->game->game_state = GAME_END;
        end_command(server, 0);
    }
    if (get_alive_players(server) == 1) {
        server->game->game_state = GAME_END;
        end_command(server, get_alive_player_id(server));
    }
}

/**
 * @brief Update the game state and player positions.
 *
 * This function updates the game tick, player positions, and sends
 * player information to all clients. It also handles debug mode if
 * enabled.
 *
 * @param server The server structure containing the game and clients.
 */
void game_tick(server_t *server)
{
    server->game->tick++;
    server->game->x += 0.1;
    update_fly_positions(server);
    if (server->debug) {
        debug(server);
    }
    player_command(server);
    check_collisions(server);
    check_end(server);
}
