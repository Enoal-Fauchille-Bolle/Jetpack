/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Map
*/

#include "Map.hpp"

Map::Map()
{
}

Map::~Map()
{
}

void Map::init(std::string message)
{
    (void)message;
    if (!_texture.loadFromFile("assets/jetpack_map.png")) {
        std::cerr << "Error loading texture" << std::endl;
        return;
    }
    _sprite.setTexture(_texture);
    _sprite.setPosition(0, 0);
    _sprite.setScale(0.1f, 0.1f);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2,
        _sprite.getGlobalBounds().height / 2);
    _sprite.setColor(sf::Color(255, 255, 255, 255));
    _isInit = true;
}

void Map::update(float deltaTime, const DittoParam& param)
{
    (void)deltaTime;
    (void)param;
    _sprite.setPosition(0, 0);
}

void Map::draw(sf::RenderWindow& window)
{
    window.draw(_sprite);
}

bool Map::isInit() const
{
    return _isInit;
}