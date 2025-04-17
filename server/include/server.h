/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Main Header
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #define MAX_CLIENTS 128
    #define BUFFER_SIZE 1024
    #define POLL_TIMEOUT 10000

    #define MAP_MAX_HEIGHT 10

    #include <arpa/inet.h>
    #include <ctype.h>
    #include <dirent.h>
    #include <netinet/in.h>
    #include <poll.h>
    #include <signal.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <unistd.h>

typedef struct server_options_s {
    int port;
    char *map_path;
    bool debug;
    bool help;
} server_options_t;

typedef struct map_s {
    char *path;
    size_t width;
    char *map[10];
} map_t;

typedef enum {
    HANDSHAKE_START,
    WAITING_FOR_ID_OK,
    WAITING_FOR_MAP_OK,
    WAITING_FOR_LOBBY_OK,
    WAITING_FOR_START_OK,
    HANDSHAKE_DONE
} handshake_state_t;

typedef struct server_s server_t;

typedef struct client_s {
    size_t id;
    server_t *server;
    int client_sockfd;
    struct sockaddr_in *client_addr;
    FILE *stream;
    handshake_state_t handshake;
    bool ready;
    bool flying;
} client_t;

typedef enum {
    GAME_START,
    GAME_IN_PROGRESS,
    GAME_END
} game_state_t;

typedef struct server_s {
    int sockfd;
    client_t clients[MAX_CLIENTS];
    struct sockaddr_in addr;
    int port;
    map_t *map;
    bool debug;
    size_t next_id;
    game_state_t game_state;
} server_t;

typedef struct command_s {
    char *name;
    int argc;
    char **argv;
} command_t;

typedef enum command_status_e {
    COMMAND_SUCCESS,
    COMMAND_FAILURE,
    COMMAND_NOT_FOUND,
    COMMAND_QUIT,
} command_status_t;

typedef struct command_handler_s {
    char *command_name;
    command_status_t (*handler)(
        command_t *command, client_t *client);
} command_handler_t;

typedef struct handshake_response_handler_s {
    handshake_state_t handshake_state;
    command_status_t (*handler)(client_t *client);
} handshake_response_handler_t;

typedef void (*option_handler_t)(
    server_options_t *opts, int *i, int ac, char **av);

typedef struct option_map_s {
    const char *option;
    option_handler_t handler;
} option_map_t;

// Get Server Options
server_options_t get_server_options(int ac, char **av);

// Map Parser
map_t *map_parser(char *path);

// Client Handler
void handle_connection(struct pollfd *fd, client_t *client);

// Socket
server_t *setup_socket(int port, bool debug);

// Connection
int process_connections(server_t *server);

// Command Parser
command_t *parse_buffer(char *buffer);

// Command Executor
command_status_t execute_command(command_t *command, client_t *client);

// Handshake Response Executor
command_status_t execute_handshake_response(client_t *client);

// Utils
char *touppercase(char *str);
char *trim(char *str);

// Destroyers
void destroy_client(client_t *, bool verbose);
void destroy_command(command_t *command);
void destroy_server(
    server_t *server, struct pollfd *fds, client_t *clients);

// Commands
command_status_t quit_command(command_t *command, client_t *client);
command_status_t ready_command(command_t *command, client_t *client);

// Handshake Responses
command_status_t id_handshake_response(client_t *client);
command_status_t map_handshake_response(client_t *client);
command_status_t lobby_handshake_response(client_t *client);
command_status_t start_handshake_response(client_t *client);

#endif /* !SERVER_H_ */
