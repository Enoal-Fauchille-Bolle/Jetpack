/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

    #include <SFML/Graphics.hpp>
    #include <iostream>
    #include <string>

class Player {
    public:
        Player();
        ~Player();

        void NewPosition(float x, float y);
        void Draw(sf::RenderWindow &window);

    protected:
    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Vector2f _position;

};

#endif /* !PLAYER_HPP_ */
