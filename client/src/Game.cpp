/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Game
*/

#include "Game.hpp"

/**
 * @brief Construct a new Game object.
 * @param ip Server IP address.
 * @param port Server port.
 */
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

/**
 * @brief Destroy the Game object.
 */
Game::~Game()
{
}

/**
 * @brief Setup the server and initialize objects.
 */
void Game::setupServer(void)
{
    gameManager.setup();
    gameManager.initObjects();
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("assets/jetpack_font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }
    text.setFont(font);
    text.setString("Waiting for players...");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);
    window.draw(text);
    window.display();
    gameManager.handleEvent(window);
}

/**
 * @brief Run the main game loop.
 */
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
            gameManager.handleEvent(window);
            window.display();
        }
    }
}
