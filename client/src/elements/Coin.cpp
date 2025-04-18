/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Coin
*/

#include "Coin.hpp"

Coin::Coin()
{
}

Coin::~Coin()
{
}

void Coin::init(std::string message)
{
    (void)message;
}

void Coin::update(float deltaTime, const DittoParam& param)
{
    (void)param;
    (void)deltaTime;
}

void Coin::draw(sf::RenderWindow& window)
{
    (void)window;
}

bool Coin::isInit() const
{
    return false;
}