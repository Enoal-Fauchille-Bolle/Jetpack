/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** GameManager
*/

#ifndef GAMEMANAGER_HPP_
    #define GAMEMANAGER_HPP_

    #include <SFML/Graphics.hpp>
    #include <unordered_map>
    #include <memory>
    #include "IElement.hpp"
    #include "Client.hpp"

class GameManager {
    public:
        GameManager();
        ~GameManager();

        void addObject(const std::string& name, std::unique_ptr<IElement> obj);

        void setup(void);

        void updateAll(float deltaTime);

        void drawAll(sf::RenderWindow& window);

        void initObjects(void);

        bool isGameStarted(void) const;

        IElement* getObject(const std::string& name);

    private:
        Client* _client;
        std::unordered_map<std::string, std::unique_ptr<IElement>> _gameObjects;
        bool _gameStarted = false;
};

#endif /* !GAMEMANAGER_HPP_ */