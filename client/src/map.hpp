/*
** EPITECH PROJECT, 2025
** B-NWP-400-NAN-4-1-jetpack-tom.feldkamp
** File description:
** map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include <iostream>
    #include <vector>
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Network.hpp>
    #include "Game.hpp"
    #include "Client.hpp"
    #include "map.hpp"

class Map {
    public:
        Map();
        ~Map();

        void init();
        void loadMap(std::string map_map);
        void close();

    protected:
    private:
        
};


#endif /* !MAP_HPP_ */
