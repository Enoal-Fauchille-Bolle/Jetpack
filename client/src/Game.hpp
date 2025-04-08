/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include "GameManager.hpp"

class Game {
    public:
        Game();
        ~Game();

        void serveur_setup();

        void game_run();

    protected:
    private:
        GameManager gameManager;

};

#endif /* !GAME_HPP_ */
