/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-tom.feldkamp
** File description:
** Game
*/

#include "Game.hpp"
#include <iostream>
#include <sstream>

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(char *ip, char *port)
{
    client = Client(ip, port);
    window.create(sf::VideoMode(800, 600), "Jetpack");
    view.setSize(800, 600);
    view.setCenter(400, 300);
    window.setView(view);

    Client newCliant(ip, port);
    client = newCliant;

    map.init();
    window_view.init();
    for (int i = 0; i < 3; i++) {
        Player newPlayer;
        Coin newCoin;
        newCoin.init();
        newPlayer.init();
        coins.push_back(newCoin);
        player.push_back(newPlayer);
    }
}

void Game::conection()
{
    while (map_loaded == false && player_loaded == false) {
        std::string message = client.get_msg();
        if (message.rfind("ID", 0) == 0) {
            std::istringstream iss(message);
            std::string id_str;

            iss >> id_str >> pid;
            if (id_str == "ID") {
                client.send_msg("OK");
                player_loaded = true;
            } else {
                client.send_msg("ERROR");
            }
        }
        if (message.rfind("MAP", 0) == 0) {
            std::istringstream iss(message);
            std::string map_str;

            iss >> map_str;
            if (map_str == "MAP") {
                client.send_msg("OK");
                map.loadMap(map_str);
                map_loaded = true;
            } else {
                client.send_msg("ERROR");
            }
        }
    }
    while (ready == false) {
        std::string message = client.get_msg();
        if (message.rfind("START", 0) == 0) {
            ready = true;
        }
    }
}

void Game::run()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space)
                    client.send_msg("FLY 1");
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space)
                    client.send_msg("FLY 0");
            }
        }
        std::string message = client.get_msg();
        if (message.rfind("PLAYER", 0) == 0) {
            std::istringstream iss(message);
            std::string player_str;
            int id;
            float x, y;
            iss >> player_str >> id >> x >> y;
            id--;
            if (player_str == "PLAYER") {
                player[id].setPosition(x, y);
            }
        }
        window.clear();
        map.run();
        window.display();
    }
}