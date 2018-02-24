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

namespace tile {
    /**
     * Whether a tile blocks entity movement
     * @param tile The tile to check
     * @return true if blocking
     */
    bool isBlocking(const Tile &tile);

    /**
     * Whether a tile is a solid surface (i.e. an entity can be on it)
     * @param tile The tile to check
     * @return true if it's a solid surface
     */
    bool isSurface(const Tile &tile);
}
std::ostream &operator<<(std::ostream &stream, const Tile &tile);

#endif //BOOM_TILE_HPP
