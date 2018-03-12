//
// Created by zeroji on 2/23/18.
//

#include "Map.hpp"

const Tile &Map::operator()(const unsigned int &x, const unsigned int &y) const {
    return tiles[x][y].tile;
}

const Tile &Map::operator()(const sf::Vector2u &pos) const {
    return tiles[pos.x][pos.y].tile;
}

Map::Map(const unsigned int &width, const unsigned int &height) :
        width(width), height(height),
        tiles(width, std::vector<TileData>(height))
{
    for (unsigned int i = 0; i < width; ++i) {
        t(i, 0) = WALL;
        t(i, height-1) = WALL;
    }
    for (unsigned int j = 0; j < height; ++j) {
        t(0, j) = WALL;
        t(width-1, j) = WALL;
    }

    for(unsigned int i = 2; i < width; i += 2)
        for(unsigned int j = 2; j < height; j += 2)
            if(t(i, j) == VOID)
                t(i, j) = BLOCK;
}

std::ostream &operator<<(std::ostream &stream, const Map &map) {
    for (int j = 0; j < map.height; ++j) {
        for (int i = 0; i < map.width; ++i)
            stream << map.tiles[i][j].tile;
        stream << std::endl;
    }
    return stream;
}

const unsigned int Map::getWidth() const {
    return width;
}

const unsigned int Map::getHeight() const {
    return height;
}

Tile &Map::t(const unsigned int &x, const unsigned int &y) {
    return tiles[x][y].tile;
}
