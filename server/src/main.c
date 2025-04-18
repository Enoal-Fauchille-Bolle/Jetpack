/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Main File
*/

#include "server.h"
#include "options.h"
#include "connection.h"

#include <unistd.h>

/**
 * @brief Set the read mode for the server.
 *
 * This function sets the read mode for the server. It is used to
 * prevent the server from blocking on read operations.
 *
 * @param a Boolean value indicating whether to set read mode or not.
 */
static void set_read(bool a)
{
    if (a == true)
        read(STDIN_FILENO, NULL, 0);
    return;
}

/**
 * @brief Display the help page for the server.
 *
 * This function prints the usage information for the server
 * command-line options.
 */
static void help_page(void)
{
    puts("USAGE: ./jetpack_server -p <port> -m <map> [-d]");
    puts("\t-p <port>\tPort of the server");
    puts("\t-m <map>\tPath to the map file");
    puts("\t-d\t\tDebug mode");
}

/**
 * @brief Check if the given path is valid.
 *
 * This function checks if the specified path exists and is accessible.
 *
 * @param path The path to check.
 * @return int 0 if the path is valid, 84 otherwise.
 */
static int check_path(char *path)
{
    if (path == NULL)
        return 84;
    if (access(path, F_OK) == -1) {
        return 84;
    }
    return 0;
}

/**
 * @brief Check the validity of command-line arguments.
 *
 * This function checks if the provided port number and path are valid.
 *
 * @param port The port number to check.
 * @param path The path to check.
 * @return int 0 if valid, 84 otherwise.
 */
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

/**
 * @brief Start the Jetpack server.
 *
 * This function initializes the server, sets up the socket, and starts
 * processing connections.
 *
 * @param port The port number for the server.
 * @param path The path to the map file.
 * @param debug Boolean value indicating whether to enable debug mode.
 * @return int 0 on success, 84 on failure.
 */
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
    printf("Waiting for connections...\n");
    return process_connections(server);
}

/**
 * @brief Main function for the Jetpack server.
 *
 * This function parses command-line arguments and starts the server.
 *
 * @param ac The number of command-line arguments.
 * @param av The command-line arguments.
 * @return int 0 on success, 84 on failure.
 */
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
