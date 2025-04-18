/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** PlayerList
*/

#include "PlayerList.hpp"

PlayerList::PlayerList()
{
}

PlayerList::~PlayerList()
{
}

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


void PlayerList::draw(sf::RenderWindow& window)
{
    for (auto &[playerData, player] : _playerList) {
        if (playerData.isInit) {
            player.Draw(window);
        }
    }
}

bool PlayerList::isInit() const
{
    if (_playerList.empty())
        return false;
    return _isAllInit;
}

bool PlayerList::PlayerListData::operator<(const PlayerListData& other) const
{
    return id < other.id;
}

bool PlayerList::PlayerListData::operator[](const PlayerListData& other) const
{
    return id == other.id;
}

bool PlayerList::PlayerListData::operator==(const PlayerListData& other) const
{
    return id == other.id && isClient == other.isClient;
}