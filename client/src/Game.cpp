/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Game
*/

#include "Game.hpp"

/**
 * @brief Construct a new Game:: Game object
 *
 * This function initializes the game manager and adds game objects to it.
 */
Game::Game()
{
    gameManager.addObject("Player", std::make_unique<PlayerList>());
    gameManager.addObject("Map", std::make_unique<Map>());
    gameManager.addObject("Coin", std::make_unique<Coin>());
    gameManager.addObject("View", std::make_unique<View>());
}

/**
 * @brief Destroy the Game:: Game object
 */
Game::~Game()
{
}

/**
 * @brief Run the game loop
 *
 * This function runs the game loop, updating and drawing all game objects.
 */
void Game::setupServer(void)
{
    while (gameManager.isGameStarted() == false) {
        gameManager.setup();
        gameManager.initObjects();
    }
}

/**
 * @brief Run the game
 *
 * This function runs the game loop, updating and drawing all game objects.
 */
void Game::runGame(void) {
    // Todo
}
