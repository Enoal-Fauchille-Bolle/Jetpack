/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Player
*/

#include "Player.hpp"

Player::Player()
{
    sf::Texture texture;
    if (!texture.loadFromFile("assets/jetpack_player.png")) {
        std::cerr << "Error loading texture" << std::endl;
        return;
    }
    _sprite.setTexture(texture);
    _sprite.setPosition(0, 0);
    _sprite.setScale(0.1f, 0.1f);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2,
        _sprite.getGlobalBounds().height / 2);
    _sprite.setColor(sf::Color(255, 255, 255, 255));
}

Player::~Player()
{
}

void Player::NewPosition(float x, float y)
{
    sf::Vector2f currentPos = _sprite.getPosition();
    sf::Vector2f newPos(currentPos.x + x, currentPos.y + y);

    _sprite.setPosition(newPos);
}

void Player::Draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
}