/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Main Header
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <cstdbool>

typedef struct client_options_s {
    char *ip;
    int port;
    bool debug;
    bool help;
} client_options_t;

#endif /* !CLIENT_HPP_ */
