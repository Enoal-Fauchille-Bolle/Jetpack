/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** main
*/

#include <iostream>

#include "client.hpp"

/**
 * @brief Parse command line arguments
 *
 * This function takes the command line arguments and parses them
 * to extract the server IP address, port, and debug mode.
 * It returns a struct containing the parsed options.
 *
 * @param ac The number of command line arguments
 * @param av The command line arguments
 * @return client_options_t A struct containing the parsed options
 */
client_options_t parseArguments(int ac, char **av)
{
    client_options_t opts = {nullptr, 0, false, false};

    for (int i = 1; i < ac; i++) {
        std::string arg(av[i]);
        if (arg == "-h" && i + 1 < ac) {
            opts.ip = av[++i];
        } else if (arg == "-p" && i + 1 < ac) {
            opts.port = std::atoi(av[++i]);
        } else if (arg == "-d") {
            opts.debug = true;
        } else if (arg == "--help") {
            opts.help = true;
        } else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            opts.help = true;
        }
    }
    return opts;
}

/**
 * @brief Display the help page for the client
 *
 * This function prints the usage and description of the client
 * command line options and controls to the standard output.
 * It provides information on how to run the client, including
 * the required arguments and their meanings.
 */
void helpPage(void)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./jetpack_client -h <ip> -p <port> [-d]" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\t-h\tIp address of the server" << std::endl;
    std::cout << "\t-p\tPort of the server" << std::endl;
    std::cout << "\t-d\tDebug mode" << std::endl;
    std::cout << "\t--help\tDisplay this help message" << std::endl;
    std::cout << "CONTROLS" << std::endl;
    std::cout << "\tSpace key\tFly" << std::endl;
}

int main(int ac, char **av)
{
    client_options_t opts = parseArguments(ac, av);

    if (opts.help) {
        helpPage();
        return 0;
    }
    if (opts.ip == nullptr || opts.port == 0) {
        helpPage();
        return 84;
    }
    // Initialize the game
    // Game game(av[1]);
    // game.run();
    return 0;
}
