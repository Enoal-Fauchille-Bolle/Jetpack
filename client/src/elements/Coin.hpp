/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Coin
*/

#ifndef COIN_HPP_
    #define COIN_HPP_

    #include "../IElement.hpp"
    #include "../IType.hpp"

class Coin : public IElement {
    public:
        Coin();
        ~Coin();

        void init(std::string message) override;
        void update(float deltaTime, const DittoParam &param) override;
        void draw(sf::RenderWindow& window) override;
        bool isInit() const override;
};

#endif /* !COIN_HPP_ */
