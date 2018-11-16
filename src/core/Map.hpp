//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_MAP_HPP
#define BOOM_MAP_HPP


#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Tile.hpp"
#include "Upgrade.hpp"
#include <map>
#include <random>
#include <memory>

class Bomb;

class Map {
    struct TileData {
        Tile tile=Tile::VOID;
        std::shared_ptr<Upgrade> upgrade=nullptr;
        std::map<const Bomb*, unsigned int> explosions;
        std::vector<const Bomb*> explosionVector;
    };

public:

    Map(const unsigned int &width, const unsigned int &height);

    const Tile &operator()(const unsigned int &x, const unsigned int &y) const;
    const Tile &operator()(const sf::Vector2u &pos) const;
    friend std::ostream &operator<<(std::ostream &stream, const Map &map);

    const unsigned int getWidth() const;

    const unsigned int getHeight() const;

    void updateBomb(const Bomb *, const sf::Vector2u &pos, const unsigned int &distance);
    void removeBomb(const Bomb *);

    const std::vector<const Bomb*> &getBombs(const sf::Vector2u &pos) const;

    const Upgrade *getUpgrade(const sf::Vector2u &pos) const;
    void removeUpgrade(const sf::Vector2u &pos);

    bool inBounds(const sf::Vector2u &pos) const;

    sf::Vector2u getPlayerBase(unsigned int id);

    bool breakTile(const sf::Vector2u &pos);

private:
    unsigned int width, height;
    TileData &td(const sf::Vector2u &pos);
    TileData &td(const unsigned int &x, const unsigned int &y);
    const TileData &td(const sf::Vector2u &pos) const;
    const TileData &td(const unsigned int &x, const unsigned int &y) const;
    Tile &t(const unsigned int &x, const unsigned int &y);
    std::vector<std::vector<TileData>> tiles;

    std::random_device rd;
    std::mt19937 gen;
    std::bernoulli_distribution dist;

    void clearSpaceAround(const sf::Vector2u &pos);
};


#endif //BOOM_MAP_HPP
