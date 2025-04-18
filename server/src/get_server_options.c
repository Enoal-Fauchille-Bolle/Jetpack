/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Get Server Options
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

/**
 * @brief Handle the port option.
 *
 * This function sets the port number for the server options.
 *
 * @param opts The server options structure.
 * @param i The index of the current argument.
 * @param ac The total number of arguments.
 * @param av The array of arguments.
 */
static void handle_port(server_options_t *opts, int *i, int ac, char **av)
{
    if (*i + 1 < ac) {
        *i += 1;
        opts->port = atoi(av[*i]);
    }
}

/**
 * @brief Handle the map option.
 *
 * This function sets the map path for the server options.
 *
 * @param opts The server options structure.
 * @param i The index of the current argument.
 * @param ac The total number of arguments.
 * @param av The array of arguments.
 */
static void handle_map(server_options_t *opts, int *i, int ac, char **av)
{
    if (*i + 1 < ac) {
        *i += 1;
        free(opts->map_path);
        opts->map_path = av[*i];
    }
}

/**
 * @brief Handle the debug option.
 *
 * This function sets the debug mode for the server options.
 *
 * @param opts The server options structure.
 * @param i The index of the current argument.
 * @param ac The total number of arguments.
 * @param av The array of arguments.
 */
static void handle_debug(server_options_t *opts, int *i, int ac, char **av)
{
    (void)i;
    (void)ac;
    (void)av;
    opts->debug = 1;
}

/**
 * @brief Handle the help option.
 *
 * This function sets the help mode for the server options.
 *
 * @param opts The server options structure.
 * @param i The index of the current argument.
 * @param ac The total number of arguments.
 * @param av The array of arguments.
 */
static void handle_help(server_options_t *opts, int *i, int ac, char **av)
{
    (void)i;
    (void)ac;
    (void)av;
    opts->help = 1;
}

/**
 * @brief Find the option handler for a given argument.
 *
 * This function searches for the option handler corresponding to the
 * provided argument.
 *
 * @param arg The argument to search for.
 * @return const option_map_t* Pointer to the option map entry, or NULL if not
 * found.
 */
static const option_map_t *find_option(const char *arg)
{
    static const option_map_t option_map[] = {{"-p", handle_port},
        {"-m", handle_map}, {"-d", handle_debug}, {"--help", handle_help},
        {"-h", handle_help}, {NULL, NULL}};

    for (const option_map_t *entry = option_map; entry->option != NULL;
        entry++) {
        if (strcmp(arg, entry->option) == 0)
            return entry;
    }
    return NULL;
}

/**
 * @brief Get the server options from command-line arguments.
 *
 * This function parses the command-line arguments and sets the server
 * options accordingly.
 *
 * @param ac The total number of arguments.
 * @param av The array of arguments.
 * @return server_options_t The server options structure.
 */
server_options_t get_server_options(int ac, char **av)
{
    server_options_t opts = {
        .port = 0, .map_path = NULL, .debug = false, .help = false};
    int i = 1;
    const option_map_t *opt;

    while (i < ac) {
        opt = find_option(av[i]);
        if (opt != NULL && opt->handler != NULL) {
            opt->handler(&opts, &i, ac, av);
        } else {
            printf("Unknown option: %s\n", av[i]);
            opts.help = true;
        }
        i++;
    }
    return opts;
}
