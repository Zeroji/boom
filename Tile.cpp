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
