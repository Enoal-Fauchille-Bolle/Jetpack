/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-tom.feldkamp
** File description:
** player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <iostream>
    #include <vector>
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Network.hpp>
    #include "Game.hpp"

class Player {
    public:
        Player();
        ~Player();

        void init();
        void setPosition(float x, float y);

    protected:
    private:
};


#endif /* !PLAYER_HPP_ */
