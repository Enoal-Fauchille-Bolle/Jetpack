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

void PlayerList::Init(std::string message)
{
    if (message.rfind("ID", 0) == 0) {
        std::string id = message.substr(3);
        int playerId = std::stoi(id);
        PlayerListData playerData;
        playerData.id = playerId;
        playerData.isClient = true;
        playerData.isInit = true;
        playerList[playerData] = std::move(Player());
    } else if (message.rfind("LOBBY", 0) == 0) {

    } else {
        return;
    }
}
void PlayerList::Update(float deltaTime)
{
}
void PlayerList::Draw(sf::RenderWindow& window)
{
}
bool PlayerList::isInit() const
{
    return all_init;
}

