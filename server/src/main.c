/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Main File
*/

#include "server.h"

static void set_read(bool a)
{
    if (a == true)
        read(STDIN_FILENO, NULL, 0);
    return;
}

static void help_page(void)
{
    puts("USAGE: ./jetpack_server -p <port> -m <map> [-d]");
    puts("\t-p <port>\tPort of the server");
    puts("\t-m <map>\tPath to the map file");
    puts("\t-d\t\tDebug mode");
}

static int check_path(char *path)
{
    if (path == NULL)
        return 84;
    if (access(path, F_OK) == -1) {
        return 84;
    }
    return 0;
}

static int check_args(int port, char *path)
{
    if (port <= 0 || port > 65535) {
        puts("Error: Invalid port number");
        return 84;
    } else if (check_path(path) == 84) {
        puts("Error: Invalid path");
        return 84;
    }
    return 0;
}

static int jetpack_server(int port, char *path, bool debug)
{
    server_t *server = setup_socket(port, debug);

    set_read(false);
    if (!server || server->sockfd == 0)
        return 84;
    server->map = map_parser(path);
    if (server->map == NULL || server->map->width == 0) {
        puts("Error: Failed to parse map");
        close(server->sockfd);
        return 84;
    }
    if (server->debug) {
        printf("Listening on port %d\n", port);
        printf("Map file: %s\n", path);
    }
    return process_connections(server);
}

int main(int ac, char **av)
{
    server_options_t options = get_server_options(ac, av);

    if (options.help) {
        help_page();
        return 0;
    }
    if (check_args(options.port, options.map_path) == 84) {
        help_page();
        return 84;
    }
    if (jetpack_server(options.port, options.map_path, options.debug) == 84) {
        puts("Error: Failed to start server");
        return 84;
    }
    return 0;
}
