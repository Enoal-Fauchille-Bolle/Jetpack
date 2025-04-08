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

        void Init(std::string message) override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        bool isInit() const override;
    private:
        struct PlayerListData {
            int id;
            bool isClient;
            bool isInit;

            bool operator<(const PlayerListData& other) const {
                return id < other.id;
            }
        };

        std::map<PlayerListData, Player> playerList;
        bool all_init;
};

#endif /* !PLAYERLIST_HPP_ */
