//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_MAP_HPP
#define BOOM_MAP_HPP


#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Tile.hpp"

class Map {
public:

    Map(const unsigned int &width, const unsigned int &height);

    const Tile &operator()(const unsigned int &x, const unsigned int &y) const;
    const Tile &operator()(const sf::Vector2u &pos) const;
    friend std::ostream &operator<<(std::ostream &stream, const Map &map);

    const unsigned int getWidth() const;

    const unsigned int getHeight() const;

private:
    unsigned int width, height;
    std::vector<std::vector<Tile>> tiles;
};


#endif //BOOM_MAP_HPP
