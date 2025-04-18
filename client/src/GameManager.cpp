/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** GameManager
*/

#include "GameManager.hpp"

/**
 * @brief Construct a new GameManager object.
 * @param ip Server IP address.
 * @param port Server port.
 */
GameManager::GameManager(char *ip, int port)
    : _client(std::make_unique<ClientHandler>(ip, std::to_string(port).c_str()))
    , _gameObjects()
    , _gameStarted(false)
    , _isFlying(false)
{
}

/**
 * @brief Destroy the GameManager object.
 */
GameManager::~GameManager()
{
    _client->sendMsg("END");
}

/**
 * @brief Add a game object.
 * @param name Name of the object.
 * @param obj Unique pointer to the object.
 */
void GameManager::addObject(const std::string &name, std::unique_ptr<IElement> obj)
{
    _gameObjects[name] = std::move(obj);
}

/**
 * @brief Setup the game manager (receive initial messages).
 */
void GameManager::setup(void)
{
    std::string message = _client->getMsg();
    if (message.rfind("ID", 0) == 0) {
        _gameObjects["Player"]->init(message);
        _client->sendMsg("OK\r\n");
    }
    if (message.rfind("MAP", 0) == 0) {
        _gameObjects["Map"]->init(message);
        _gameObjects["View"]->init(message);
        _gameObjects["Coin"]->init(message);
        _client->sendMsg("OK\r\n");
    }

}

/**
 * @brief Update all game objects.
 * @param deltaTime Time since last update.
 */
void GameManager::updateAll(float deltaTime)
{
    std::string msg = _client->getMsg();
    DittoParam msg_parsed;

    if (msg.rfind("PLAYER", 0) == 0) {
        std::istringstream iss(msg);
        std::string tag;
        int playerId;
        float posX, posY;
        int score;
        bool flyStatus;

        iss >> tag >> playerId >> posX >> posY >> score >> flyStatus;
        msg_parsed = std::make_tuple(playerId, posX, posY, flyStatus);
        _gameObjects["Player"]->update(deltaTime, msg_parsed);
        _gameObjects["View"]->update(deltaTime, msg_parsed);
    } else if (msg.rfind("COIN", 0) == 0) {
        std::istringstream iss(msg);
        std::string tag;
        int coinId;
        float posX, posY;

        iss >> tag >> coinId >> posX >> posY;
        msg_parsed = std::make_tuple(coinId, posX, posY);
        _gameObjects["Coin"]->update(deltaTime, msg_parsed);
    } else {
        if (msg.rfind("END", 0) == 0) {
            _gameStarted = false;
            return;
        }
        std::cerr << "Unknown message: " << msg << std::endl;
    }
    _client->sendMsg("OK\r\n");
}

/**
 * @brief Draw all game objects.
 * @param window The SFML render window.
 */
void GameManager::drawAll(sf::RenderWindow &window)
{
    for (auto &[name, obj] : _gameObjects) {
        obj->draw(window);
    }
}

/**
 * @brief Initialize all game objects.
 */
void GameManager::initObjects(void)
{
    for (auto &[name, obj] : _gameObjects) {
        if (!obj->isInit()) {
            std::cerr << "Object " << name << " is not initialized." << std::endl;
            return;
        }
    }
    _gameStarted = true;
    _client->sendMsg("READY\r\n");
}

/**
 * @brief Check if the game has started.
 * @return true if started, false otherwise.
 */
bool GameManager::isGameStarted() const
{
    return _gameStarted;
}

/**
 * @brief Get a game object by name.
 * @param name Name of the object.
 * @return Pointer to the object, or nullptr if not found.
 */
IElement *GameManager::getObject(const std::string &name)
{
    auto it = _gameObjects.find(name);

    if (it != _gameObjects.end()) {
        return it->second.get();
    }
    return nullptr;
}

/**
 * @brief Handle SFML window events.
 * @param window The SFML render window.
 */
void GameManager::handleEvent(sf::RenderWindow &window)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space
                && _isFlying == false) {
                _client->sendMsg("FLY 1");
                _isFlying = true;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Space
                && _isFlying == true) {
                _client->sendMsg("FLY 0");
                _isFlying = false;
            }
        }
    }
}