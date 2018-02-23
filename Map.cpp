//
// Created by zeroji on 2/23/18.
//

#include "Map.hpp"

const Tile &Map::operator()(const unsigned int &x, const unsigned int &y) {
    return tiles[x][y];
}

Map::Map(const unsigned int width, const unsigned int height) :
        width(width), height(height),
        tiles(width, std::vector<Tile>(height, VOID))
{
    for (int i = 0; i < width; ++i) {
        tiles[i][0] = WALL;
        tiles[i][height-1] = WALL;
    }
    for (int j = 0; j < height; ++j) {
        tiles[0][j] = WALL;
        tiles[width-1][j] = WALL;
    }
}

std::ostream &operator<<(std::ostream &stream, const Map &map) {
    for (int j = 0; j < map.height; ++j) {
        for (int i = 0; i < map.width; ++i)
            stream << map.tiles[i][j];
        stream << std::endl;
    }
    return stream;
}
