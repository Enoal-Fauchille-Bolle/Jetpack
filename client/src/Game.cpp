/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(char *ip, int port) : gameManager(ip, port)
{

    window.create(sf::VideoMode(800, 600), "Jetpack Client");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    gameManager.addObject("Player", std::make_unique<PlayerList>());
    gameManager.addObject("Map", std::make_unique<Map>());
    gameManager.addObject("Coin", std::make_unique<Coin>());
    gameManager.addObject("View", std::make_unique<View>());
}

Game::~Game()
{
}

void Game::setupServer(void)
{
    gameManager.setup();
    gameManager.initObjects();
}

void Game::runGame(void)
{
    sf::Clock clock;

    while (window.isOpen()) {
        if (gameManager.isGameStarted() == false) {
            setupServer();
        } else {
            sf::Time deltaTime = clock.restart();
            gameManager.updateAll(deltaTime.asSeconds());
            gameManager.drawAll(window);
            window.display();
        }
    }
}
