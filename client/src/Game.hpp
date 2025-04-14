/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include <iostream>

    #include "Client.hpp"
    #include "GameManager.hpp"
    #include "elements/Coin.hpp"
    #include "elements/Map.hpp"
    #include "elements/PlayerList.hpp"
    #include "elements/View.hpp"

class Game {
    public:
        Game();
        ~Game();

        void setupServer(void);

        void runGame(void);

    private:
        GameManager gameManager;
};

#endif /* !GAME_HPP_ */
