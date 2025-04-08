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

        void Init(std::string message) override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        bool isInit() const override;

    private:
        sf::View view;
};

#endif /* !VIEW_HPP_ */
