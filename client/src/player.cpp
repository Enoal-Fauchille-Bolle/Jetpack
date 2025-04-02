/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-tom.feldkamp
** File description:
** player
*/


#include "player.hpp"
#include <iostream>

Player::Player()
{
}

Player::~Player()
{
}

void Player::init()
{
    std::cout << "Player initialized" << std::endl;
}

void Player::setPosition(float x, float y)
{
    std::cout << "Player position set to: " << x << ", " << y << std::endl;
}

void Player::run()
{
    std::cout << "Player running" << std::endl;
}