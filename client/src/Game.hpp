/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-tom.feldkamp
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include <iostream>
    #include <vector>
    #include "map.hpp"
    #include "view.hpp"
    #include "player.hpp"
    #include "Coin.hpp"
    #include "Client.hpp"

class Game {
    public:
        Game();
        ~Game();

        void init(char *ip, char *port);
        void conection();
        void run();
        void close();

    protected:
        bool all_load();
    private:
        std::vector<Player> player;
        std::vector<Coin> coins;
        Map map = Map();
        window_View window_view = window_View();
        Client client;

        sf::RenderWindow window;
        sf::View view;

        bool ready = false;
        bool map_loaded = false;
        bool player_loaded = false;

        int pid;
};

#endif /* !GAME_HPP_ */
