/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include "../IElement.hpp"

class Map : public IElement {
    public:
        Map();
        ~Map();

        void init(std::string message) override;
        void update(float deltaTime) override;
        void draw(sf::RenderWindow& window) override;
        bool isInit() const override;
};

#endif /* !MAP_HPP_ */
