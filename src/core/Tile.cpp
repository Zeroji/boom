//
// Created by zeroji on 2/23/18.
//

#include "Tile.hpp"

std::ostream &operator<<(std::ostream &stream, const Tile &tile) {
    switch (tile) {
        case Tile::VOID:  stream << " "; break;
        case Tile::BLOCK: stream << "-"; break;
        case Tile::SOLID_BLOCK: stream << "O"; break;
        case Tile::WALL:  stream << "X"; break;
    }
    return stream;
}

bool ::tile::isBlocking(const Tile &tile) {
    switch (tile) {
        case Tile::VOID:
            return false;
        case Tile::BLOCK:
        case Tile::SOLID_BLOCK:
        case Tile::WALL:
            return true;
    }
    return false;
}

bool ::tile::isSurface(const Tile &tile) {
    if(tile::isBlocking(tile))
        return false;
    switch (tile) {
        case Tile::VOID:
            return true;
        default:
            return false;
    }
}

bool ::tile::isBreakable(const Tile &tile) {
    switch (tile) {
        case Tile::BLOCK:
            return true;
        default:
            return false;
    }
}