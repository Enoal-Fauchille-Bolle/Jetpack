/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Coin
*/

#ifndef COIN_HPP_
    #define COIN_HPP_

    #include "../IElement.hpp"

class Coin : public IElement {
    public:
        Coin();
        ~Coin();

        void Init(std::string message) override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        bool isInit() const override;

    protected:
    private:
};

#endif /* !COIN_HPP_ */
