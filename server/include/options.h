/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Options Header
*/

#ifndef OPTIONS_H_
    #define OPTIONS_H_

    #include <stdbool.h>

typedef struct server_options_s {
    int port;
    char *map_path;
    bool debug;
    bool help;
} server_options_t;

typedef void (*option_handler_t)(
    server_options_t *opts, int *i, int ac, char **av);

typedef struct option_map_s {
    const char *option;
    option_handler_t handler;
} option_map_t;

server_options_t get_server_options(int ac, char **av);

#endif /* !OPTIONS_H_ */
