/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** GameManager
*/

#include "GameManager.hpp"

/**
 * @brief Construct a new Game Manager:: Game Manager object
 */
GameManager::GameManager()
{
}

/**
 * @brief Destroy the Game Manager:: Game Manager object
 */
GameManager::~GameManager()
{
}

/**
 * @brief Add an object to the game manager
 *
 * This function adds an object to the game manager's list of game objects.
 *
 * @param name The name of the object
 * @param obj The object to add
 */
void GameManager::addObject(
    const std::string &name, std::unique_ptr<IElement> obj)
{
    _gameObjects[name] = std::move(obj);
}

/**
 * @brief Setup the game manager
 *
 * This function sets up the game manager by initializing the game objects
 * based on the messages received from the client.
 */
void GameManager::setup(void)
{
    std::string message = _client->getMsg();

    if (message.rfind("ID", 0) == 0) {
        _gameObjects["Player"]->init(message);
    }
    if (message.rfind("MAP", 0) == 0) {
        _gameObjects["Map"]->init(message);
        _gameObjects["View"]->init(message);
        _gameObjects["Coin"]->init(message);
    }
    if (message.rfind("LOBBY", 0) == 0) {
        _gameObjects["Player"]->init(message);
    }
}

/**
 * @brief Update all game objects
 *
 * This function updates all game objects in the game manager.
 *
 * @param deltaTime The time since the last update
 */
void GameManager::updateAll(float deltaTime)
{
    for (auto &[name, obj] : _gameObjects) {
        obj->update(deltaTime);
    }
}

/**
 * @brief Draw all game objects
 *
 * This function draws all game objects in the game manager.
 *
 * @param window The window to draw the objects on
 */
void GameManager::drawAll(sf::RenderWindow &window)
{
    for (auto &[name, obj] : _gameObjects) {
        obj->draw(window);
    }
}

/**
 * @brief Initialize all game objects
 *
 * This function initializes all game objects in the game manager.
 */
void GameManager::initObjects(void)
{
    for (auto &[name, obj] : _gameObjects) {
        if (!obj->isInit()) {
            return;
        }
    }
    _client->sendMsg("READY");
}

/**
 * @brief Check if the game has started
 *
 * This function checks if the game has started.
 *
 * @return true if the game has started, false otherwise
 */
bool GameManager::isGameStarted() const
{
    return _gameStarted;
}

/**
 * @brief Get an object by name
 *
 * This function retrieves an object from the game manager by its name.
 *
 * @param name The name of the object
 * @return A pointer to the object, or nullptr if not found
 */
IElement *GameManager::getObject(const std::string &name)
{
    auto it = _gameObjects.find(name);

    if (it != _gameObjects.end()) {
        return it->second.get();
    }
    return nullptr;
}
