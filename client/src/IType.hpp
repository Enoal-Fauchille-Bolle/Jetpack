/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** IType
*/

#ifndef ITYPE_HPP_
    #define ITYPE_HPP_

    #include <variant>
    #include <tuple>
    #include <string>

using DittoParam = std::variant<std::tuple<int, float, float, bool>, std::tuple<int, float, float>,std::string>;

typedef struct client_options_s {
    char *ip;
    int port;
    bool debug;
    bool help;
} client_options_t;


#endif /* !ITYPE_HPP_ */
