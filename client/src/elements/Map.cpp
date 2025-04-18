/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Map
*/

#include "Map.hpp"

/**
 * @brief Construct a new Map object.
 */
Map::Map()
{
}

/**
 * @brief Destroy the Map object.
 */
Map::~Map()
{
}

/**
 * @brief Initialize the map with a message.
 * @param message The initialization message.
 */
void Map::init(std::string message)
{
    (void)message;
    if (!_texture.loadFromFile("assets/background.png")) {
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

/**
 * @brief Update the map state.
 * @param deltaTime Time since last update.
 * @param param Parameters for update.
 */
void Map::update(float deltaTime, const DittoParam& param)
{
    (void)deltaTime;
    (void)param;
    _sprite.setPosition(0, 0);
}

/**
 * @brief Draw the map on the window.
 * @param window The SFML render window.
 */
void Map::draw(sf::RenderWindow& window)
{
    window.draw(_sprite);
}

/**
 * @brief Check if the map is initialized.
 * @return true if initialized, false otherwise.
 */
bool Map::isInit() const
{
    return _isInit;
}