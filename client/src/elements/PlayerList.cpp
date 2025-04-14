/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** PlayerList
*/

#include "PlayerList.hpp"

/**
 * @brief Construct a new Player List:: Player List object
 */
PlayerList::PlayerList()
{
}

/**
 * @brief Destroy the Player List:: Player List object
 */
PlayerList::~PlayerList()
{
}

/**
 * @brief Initialize the PlayerList object
 *
 * This function initializes the PlayerList object by parsing the given message.
 * It extracts the player ID and initializes the player data accordingly.
 *
 * @param message The message to parse for player initialization.
 */
void PlayerList::init(std::string message)
{
    std::string id;
    int playerId;
    PlayerListData playerData;

    if (message.rfind("ID", 0) == 0) {
        id = message.substr(3);
        playerId = std::stoi(id);
        playerData.id = playerId;
        playerData.isClient = true;
        playerData.isInit = true;
        _playerList[playerData] = std::move(Player());
    } else if (message.rfind("LOBBY", 0) == 0) {

    } else {
        return;
    }
}

/**
 * @brief Update the PlayerList object
 *
 * This function updates the PlayerList object. It is currently empty and does not perform any operations.
 *
 * @param deltaTime The time elapsed since the last update.
 */
void PlayerList::update(float deltaTime)
{
    (void)deltaTime;
    // Todo
}

/**
 * @brief Draw the PlayerList object
 *
 * This function draws the PlayerList object. It is currently empty and does not perform any operations.
 *
 * @param window The render window to draw on.
 */
void PlayerList::draw(sf::RenderWindow& window)
{
    (void)window;
    // Todo
}

/**
 * @brief Check if the PlayerList object is initialized
 *
 * This function checks if the PlayerList object is initialized.
 *
 * @return true if the PlayerList object is initialized, false otherwise.
 */
bool PlayerList::isInit() const
{
    return _isAllInit;
}

/**
 * @brief Compare two PlayerListData objects
 *
 * This function compares two PlayerListData objects based on their IDs.
 *
 * @param other The other PlayerListData object to compare with.
 * @return true if this object is less than the other, false otherwise.
 */
bool PlayerList::PlayerListData::operator<(const PlayerListData& other) const
{
    return id < other.id;
}
