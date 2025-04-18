/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include "../IElement.hpp"
    #include "../IType.hpp"
    #include <SFML/Graphics.hpp>
    #include <iostream>

class Map : public IElement {
    public:
        Map();
        ~Map();

        void init(std::string message) override;
        void update(float deltaTime, const DittoParam &param) override;
        void draw(sf::RenderWindow& window) override;
        bool isInit() const override;

    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Vector2f _position;
        bool _isInit = false;
};

#endif /* !MAP_HPP_ */
