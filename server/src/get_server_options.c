/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Get Server Options
*/

#include "server.h"

static void handle_port(server_options_t *opts, int *i, int ac, char **av)
{
    if (*i + 1 < ac) {
        *i += 1;
        opts->port = atoi(av[*i]);
    }
}

static void handle_map(server_options_t *opts, int *i, int ac, char **av)
{
    if (*i + 1 < ac) {
        *i += 1;
        free(opts->map_path);
        opts->map_path = av[*i];
    }
}

static void handle_debug(server_options_t *opts, int *i, int ac, char **av)
{
    (void)i;
    (void)ac;
    (void)av;
    opts->debug = 1;
}

static void handle_help(server_options_t *opts, int *i, int ac, char **av)
{
    (void)i;
    (void)ac;
    (void)av;
    opts->help = 1;
}

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
