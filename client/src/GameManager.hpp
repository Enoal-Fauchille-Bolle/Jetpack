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
        #include <variant>
        #include "IElement.hpp"
        #include "ClientHandler.hpp"
        #include "IType.hpp"
        #include <sstream>

    class GameManager {
        public:
            GameManager(char *ip, int port);
            ~GameManager();

            void addObject(const std::string& name, std::unique_ptr<IElement> obj);

            void setup(void);

            void updateAll(float deltaTime);

            void drawAll(sf::RenderWindow& window);

            void initObjects(void);

            bool isGameStarted(void) const;

            void handleEvent(sf::RenderWindow& window);

            IElement* getObject(const std::string& name);

        private:
            std::unique_ptr<ClientHandler> _client;
            std::unordered_map<std::string, std::unique_ptr<IElement>> _gameObjects;
            bool _gameStarted = false;

            bool _isFlying = false;
    };

    #endif /* !GAMEMANAGER_HPP_ */