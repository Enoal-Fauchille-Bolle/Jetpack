/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Coin
*/

#include "Coin.hpp"

/**
 * @brief Construct a new Coin object.
 */
Coin::Coin()
{
}

/**
 * @brief Destroy the Coin object.
 */
Coin::~Coin()
{
}

/**
 * @brief Initialize the coin with a message.
 * @param message The initialization message.
 */
void Coin::init(std::string message)
{
    (void)message;
}

/**
 * @brief Update the coin state.
 * @param deltaTime Time since last update.
 * @param param Parameters for update.
 */
void Coin::update(float deltaTime, const DittoParam& param)
{
    (void)param;
    (void)deltaTime;
}

/**
 * @brief Draw the coin on the window.
 * @param window The SFML render window.
 */
void Coin::draw(sf::RenderWindow& window)
{
    (void)window;
}

/**
 * @brief Check if the coin is initialized.
 * @return true if initialized, false otherwise.
 */
bool Coin::isInit() const
{
    return false;
}