/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** View
*/

#ifndef VIEW_HPP_
    #define VIEW_HPP_

    #include "../IElement.hpp"

class View : public IElement {
    public:
        View();
        ~View();

        void init(std::string message) override;
        void update(float deltaTime) override;
        void draw(sf::RenderWindow& window) override;
        bool isInit() const override;

    private:
        sf::View _view;
};

#endif /* !VIEW_HPP_ */
