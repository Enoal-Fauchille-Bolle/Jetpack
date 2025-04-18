/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** main
*/

#include <iostream>

#include "Game.hpp"
#include "IType.hpp"

/**
 * @brief Parse command line arguments.
 * @param ac Argument count.
 * @param av Argument vector.
 * @return Parsed client options.
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
 * @brief Display the help page.
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

/**
 * @brief Main entry point.
 * @param ac Argument count.
 * @param av Argument vector.
 * @return Exit code.
 */
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
    Game game(opts.ip, opts.port);
    game.runGame();
    return 0;
}
