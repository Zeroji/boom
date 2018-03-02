//
// Created by zeroji on 2/26/18.
//

#include <map>
#include "Direction.hpp"

sf::Vector2u operator+(const sf::Vector2u &pos, const Direction &dir) {
    sf::Vector2u res(pos);
    return (res += dir);
}

sf::Vector2u &operator+=(sf::Vector2u &pos, const Direction &dir) {
    switch (dir) {
        case UP:    pos.y -= 1; break;
        case DOWN:  pos.y += 1; break;
        case LEFT:  pos.x -= 1; break;
        case RIGHT: pos.x += 1; break;
        default: break;
    }
    return pos;
}
