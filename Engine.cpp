//
// Created by zeroji on 2/23/18.
//

#include "Engine.hpp"

Engine::Engine(): map(13, 9) {}

const Map &Engine::getMap() const {
    return map;
}

bool Engine::isValid(const sf::Vector2u &entityPos) const {
    std::vector<sf::Vector2u> checks;
    checks.push_back(entityPos / 2u);
    if(entityPos.x % 2 == 1) checks.emplace_back(sf::Vector2u(entityPos.x / 2u + 1, entityPos.y / 2u));
    if(entityPos.y % 2 == 1) checks.emplace_back(entityPos.x / 2u, entityPos.y / 2u + 1);
    if(entityPos.x % 2 == 1 && entityPos.y % 2 == 1) checks.emplace_back(entityPos.x / 2u + 1, entityPos.y / 2u + 1);
    bool surface = false;
    for(auto &pos: checks) {
        if (isBlocking(pos))
            return false;
        if (isSurface(pos))
            surface = true;
    }
    return surface;
}
