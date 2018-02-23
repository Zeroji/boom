//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_MAP_HPP
#define BOOM_MAP_HPP


#include <vector>
#include "Tile.hpp"

class Map {
public:

    Map(const unsigned int width, const unsigned int height);

    const Tile &operator()(const unsigned int &x, const unsigned int &y);
    friend std::ostream &operator<<(std::ostream &stream, const Map &map);

private:
    const unsigned int width, height;
    std::vector<std::vector<Tile>> tiles;
};


#endif //BOOM_MAP_HPP
