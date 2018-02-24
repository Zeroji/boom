//
// Created by zeroji on 2/23/18.
//

#include "Tile.hpp"

std::ostream &operator<<(std::ostream &stream, const Tile &tile) {
    switch (tile) {
        case VOID:  stream << " "; break;
        case BLOCK: stream << "-"; break;
        case WALL:  stream << "X"; break;
    }
    return stream;
}

bool ::tile::isBlocking(const Tile &tile) {
    switch (tile) {
        case VOID:
            return false;
        case BLOCK:
        case WALL:
            return true;
    }
    return false;
}

bool ::tile::isSurface(const Tile &tile) {
    if(tile::isBlocking(tile))
        return false;
    switch (tile) {
        case VOID:
            return true;
        default:
            return false;
    }
}
