/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** PlayerList
*/

#include "PlayerList.hpp"

/**
 * @brief Construct a new PlayerList object.
 */
PlayerList::PlayerList()
{
}

/**
 * @brief Destroy the PlayerList object.
 */
PlayerList::~PlayerList()
{
}

/**
 * @brief Add a new player to the list.
 * @param id Player ID.
 * @param isClient True if this player is the client.
 */
void PlayerList::newPlayer(int id, bool isClient)
{
    if (isClient) {
        _localId = id;
        _isAllInit = true;
    }
    PlayerListData playerData;
    playerData.id = id;
    playerData.isClient = isClient;
    playerData.isInit = true;
    _playerList[playerData] = std::move(Player());
}

/**
 * @brief Initialize the player list with a message.
 * @param message The initialization message.
 */
void PlayerList::init(std::string message)
{
    std::string id;
    int playerId;

    if (message.rfind("ID", 0) == 0) {
        id = message.substr(3);
        playerId = std::stoi(id);
        newPlayer(playerId, true);
        _isAllInit = true;
    } else {
        return;
    }
}

/**
 * @brief Update all players in the list.
 * @param deltaTime Time since last update.
 * @param param Parameters for update.
 */
void PlayerList::update(float deltaTime, const DittoParam &param)
{
    (void)deltaTime;
    std::visit([&](auto&& value) {
        using T = std::decay_t<decltype(value)>;

        if constexpr (std::is_same_v<T, std::tuple<int, float, float, bool>>) {
            auto [playerId, posX, posY, isFly] = value;
            PlayerListData playerData;
            playerData.id = playerId;
            playerData.isInit = true;
            if (_playerList.find(playerData) != _playerList.end()) {
                _playerList[playerData].NewPosition(posX, posY);
            } else {
                newPlayer(playerId, false);
                _playerList[playerData].NewPosition(posX, posY);
            }
        }
    }, param);
}

/**
 * @brief Draw all players in the list.
 * @param window The SFML render window.
 */
void PlayerList::draw(sf::RenderWindow& window)
{
    for (auto &[playerData, player] : _playerList) {
        if (playerData.isInit) {
            player.Draw(window);
        }
    }
}

/**
 * @brief Check if all players are initialized.
 * @return true if all initialized, false otherwise.
 */
bool PlayerList::isInit() const
{
    return _isAllInit;
}

/**
 * @brief Compare PlayerListData objects for ordering.
 * @param other The other PlayerListData.
 * @return true if this < other.
 */
bool PlayerList::PlayerListData::operator<(const PlayerListData& other) const
{
    return id < other.id;
}

/**
 * @brief Compare PlayerListData objects for equality (operator[]).
 * @param other The other PlayerListData.
 * @return true if ids are equal.
 */
bool PlayerList::PlayerListData::operator[](const PlayerListData& other) const
{
    return id == other.id;
}

/**
 * @brief Compare PlayerListData objects for equality.
 * @param other The other PlayerListData.
 * @return true if ids and isClient are equal.
 */
bool PlayerList::PlayerListData::operator==(const PlayerListData& other) const
{
    return id == other.id && isClient == other.isClient;
}