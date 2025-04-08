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
    private:
        std::unordered_map<std::string, std::unique_ptr<IElement>> gameObjects;
        bool gameStarted = false;
        Client* client;

    public:
        void AddObject(const std::string& name, std::unique_ptr<IElement> obj) {
            gameObjects[name] = std::move(obj);
        }

        void setup() {
            std::string message = client->get_msg();
            if (message.rfind("ID", 0) == 0) {
                gameObjects["Player"]->Init(message);
            }
            if (message.rfind("MAP", 0) == 0) {
                gameObjects["Map"]->Init(message);
                gameObjects["View"]->Init(message);
                gameObjects["Coin"]->Init(message);
            }
            if (message.rfind("LOBBY", 0) == 0) {
                gameObjects["Player"]->Init(message);
            }
        }

        void UpdateAll(float deltaTime) {
            for (auto& [name, obj] : gameObjects) {
                obj->Update(deltaTime);
            }
        }

        void DrawAll(sf::RenderWindow& window) {
            for (auto& [name, obj] : gameObjects) {
                obj->Draw(window);
            }
        }

        void all_init() {
            for (auto& [name, obj] : gameObjects) {
                if (!obj->isInit()) {
                    return;
                }
            }
            client->send_msg("READY");
        }

        bool get_gameStarted() const {
            return gameStarted;
        }

        IElement* GetObject(const std::string& name) {
            auto it = gameObjects.find(name);
            if (it != gameObjects.end()) {
                return it->second.get();
            }
            return nullptr;
        }
};

#endif /* !GAMEMANAGER_HPP_ */