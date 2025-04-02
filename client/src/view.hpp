/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-tom.feldkamp
** File description:
** view
*/

#ifndef VIEW_HPP_
    #define VIEW_HPP_

    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>

class window_View {
    public:
        window_View();
        ~window_View();

        void init();
        void run();
        void close();

    protected:
    private:
        sf::View view;
};

#endif /* !VIEW_HPP_ */
