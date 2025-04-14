/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** IElement
*/

#ifndef IELEMENT_HPP_
    #define IELEMENT_HPP_

    #include <SFML/Graphics.hpp>

class IElement {
    public:
        virtual void init(std::string message) = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw(sf::RenderWindow &window) = 0;
        virtual bool isInit() const = 0;
};

#endif /* !IELEMENT_HPP_ */
