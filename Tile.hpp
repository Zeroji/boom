//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_TILE_HPP
#define BOOM_TILE_HPP

#include <ostream>

enum Tile {
    VOID,
    BLOCK,
    WALL
};

std::ostream &operator<<(std::ostream &stream, const Tile &tile);

#endif //BOOM_TILE_HPP
