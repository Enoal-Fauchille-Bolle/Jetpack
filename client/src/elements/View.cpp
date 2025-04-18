/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** View
*/

#include "View.hpp"

/**
 * @brief Construct a new View object.
 */
View::View()
{
    sf::View view;
    view.setSize(1920, 1080);
    view.setCenter(960, 540);
    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    _view = view;
}

/**
 * @brief Destroy the View object.
 */
View::~View()
{
}

/**
 * @brief Initialize the view with a message.
 * @param message The initialization message.
 */
void View::init(std::string message)
{
    (void)message;
}

/**
 * @brief Update the view state.
 * @param deltaTime Time since last update.
 * @param param Parameters for update.
 */
void View::update(float deltaTime, const DittoParam& param)
{
    (void)deltaTime;
    auto [playerId, posX, posY, isFly] = std::get<std::tuple<int, float, float, bool>>(param);
    sf::Vector2f newPos(540, posY);
    _view.setCenter(newPos);
    _view.setSize(1920, 1080);
    _view.setRotation(0);
}

/**
 * @brief Draw the view on the window.
 * @param window The SFML render window.
 */
void View::draw(sf::RenderWindow& window)
{
    window.setView(_view);
    window.clear(sf::Color(0, 0, 0));
    window.display();
}

/**
 * @brief Check if the view is initialized.
 * @return true if initialized, false otherwise.
 */
bool View::isInit() const
{
    return true;
}
