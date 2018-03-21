//
// Created by zeroji on 2/23/18.
//

#include "Map.hpp"
#include "Bomb.hpp"
#include "Direction.hpp"

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

Map::TileData &Map::td(const unsigned int &x, const unsigned int &y) {
    return tiles[x][y];
}

Tile &Map::t(const unsigned int &x, const unsigned int &y) {
    return td(x, y).tile;
}

void Map::updateBomb(const Bomb *bomb, const sf::Vector2u &pos, const unsigned int &distance) {
    Map::TileData &data = td(pos.x, pos.y);
    data.explosions[bomb] = distance;
    data.explosionVector.clear();
    for(auto it: data.explosions)
        data.explosionVector.emplace_back(it.first);
    std::sort(data.explosionVector.begin(), data.explosionVector.end(), [data](const Bomb *a, const Bomb *b) { return data.explosions.at(a) - data.explosions.at(b); });
}

void Map::removeBomb(const Bomb *bomb) {
    static const Direction dirs[4] = {UP, DOWN, LEFT, RIGHT};
    for(const auto &dir: dirs) {
        sf::Vector2u pos(bomb->pos / 2u);
        for (int i = 0; i < bomb->radius; ++i) {
            pos += dir;
            if(!inBounds(pos))
                continue;
            TileData &data = td(pos.x, pos.y);
            data.explosions.erase(bomb);
            data.explosionVector.erase(std::remove(data.explosionVector.begin(), data.explosionVector.end(), bomb), data.explosionVector.end());
        }
    }
    sf::Vector2u pos(bomb->pos / 2u);
    TileData &data = td(pos.x, pos.y);
    data.explosions.erase(bomb);
    data.explosionVector.erase(std::remove(data.explosionVector.begin(), data.explosionVector.end(), bomb), data.explosionVector.end());
}

const std::vector<const Bomb *> &Map::getBombs(const sf::Vector2u &pos) const {
    return tiles[pos.x][pos.y].explosionVector;
}

bool Map::inBounds(const sf::Vector2u &pos) const {
    return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
}
