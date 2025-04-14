/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** PlayerList
*/

#ifndef PLAYERLIST_HPP_
    #define PLAYERLIST_HPP_

    #include "../IElement.hpp"
    #include "Player.hpp"

class PlayerList : public IElement {
    public:
        PlayerList();
        ~PlayerList();

        void init(std::string message) override;
        void update(float deltaTime) override;
        void draw(sf::RenderWindow& window) override;
        bool isInit() const override;

    private:
        struct PlayerListData {
            int id;
            bool isClient;
            bool isInit;

            bool operator<(const PlayerListData& other) const;
        };

        std::map<PlayerListData, Player> _playerList;
        bool _isAllInit = false;
};

#endif /* !PLAYERLIST_HPP_ */
