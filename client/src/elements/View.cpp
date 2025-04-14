/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** View
*/

#include "View.hpp"

/**
 * @brief Construct a new View:: View object
 */
View::View()
{
}

/**
 * @brief Destroy the View:: View object
 */
View::~View()
{
}

/**
 * @brief Initialize the View object
 *
 * This function initializes the View object. It is currently empty and does not perform any operations.
 *
 * @param message The message to parse for view initialization.
 */
void View::init(std::string message)
{
    (void)message;
    // Todo
}

/**
 * @brief Update the View object
 *
 * This function updates the View object. It is currently empty and does not perform any operations.
 *
 * @param deltaTime The time elapsed since the last update.
 */
void View::update(float deltaTime)
{
    (void)deltaTime;
    // Todo
}

/**
 * @brief Draw the View object
 *
 * This function draws the View object. It is currently empty and does not perform any operations.
 *
 * @param window The window to draw the View object on.
 */
void View::draw(sf::RenderWindow& window)
{
    (void)window;
    // Todo
}

/**
 * @brief Check if the View object is initialized
 *
 * This function checks if the View object is initialized. It currently returns false.
 *
 * @return true if the View object is initialized, false otherwise.
 */
bool View::isInit() const
{
    return false;
}
