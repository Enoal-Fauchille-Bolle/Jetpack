/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Game
*/

#include "Game.hpp"
#include "element/PlayerList.hpp"
#include "element/Map.hpp"
#include "element/Coin.hpp"
#include "element/View.hpp"
#include "GameManager.hpp"
#include "Client.hpp"
#include <iostream>

Game::Game()
{
    gameManager.AddObject("Player", std::make_unique<PlayerList>());
    gameManager.AddObject("Map", std::make_unique<Map>());
    gameManager.AddObject("Coin", std::make_unique<Coin>());
    gameManager.AddObject("View", std::make_unique<View>());
}

Game::~Game()
{
}

void Game::serveur_setup()
{
    while (gameManager.get_gameStarted() == false) {
        gameManager.setup();
        gameManager.all_init();
    }
}