/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** View
*/

#include "View.hpp"

View::View()
{
    sf::View view;
    view.setSize(1920, 1080);
    view.setCenter(960, 540);
    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    _view = view;
}

View::~View()
{
}

void View::init(std::string message)
{
    (void)message;
}

void View::update(float deltaTime, const DittoParam& param)
{
    (void)deltaTime;
    auto [playerId, posX, posY, isFly] = std::get<std::tuple<int, float, float, bool>>(param);
    sf::Vector2f newPos(540, posY);
    _view.setCenter(newPos);
    _view.setSize(1920, 1080);
    _view.setRotation(0);
}

void View::draw(sf::RenderWindow& window)
{
    window.setView(_view);
    window.clear(sf::Color(0, 0, 0));
    window.display();
}

bool View::isInit() const
{
    return false;
}
