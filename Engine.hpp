//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_ENGINE_HPP
#define BOOM_ENGINE_HPP


#include "Map.hpp"

class Engine {
public:
    Engine();

    const Map &getMap() const;

    inline bool isBlocking(sf::Vector2u &pos) const { return tile::isBlocking(map(pos)); }
    inline bool isSurface(sf::Vector2u &pos) const { return tile::isSurface(map(pos)); }

    bool isValid(const sf::Vector2u &entityPos) const;

private:
    Map map;
};


#endif //BOOM_ENGINE_HPP
