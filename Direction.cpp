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

Direction operator+(const Direction &dir, const int &rotation) {
    auto rot = static_cast<int8_t>(rotation % 4);
    auto direction = static_cast<int8_t>(dir);
    direction += rot;
    if(direction < 0) direction += 4;
    if(direction > 3) direction -= 4;
    return static_cast<Direction>(direction);
}

Direction operator-(const Direction &dir, const int &rotation) {
    return dir + (-rotation);
}

Direction &operator+=(Direction &dir, const int &rotation) {
    dir = dir + rotation;
    return dir;
}

Direction &operator-=(Direction &dir, const int &rotation) {
    dir += (-rotation);
    return dir;
}

Direction &operator++(Direction &dir) {
    dir += 1;
    return dir;
}

Direction &operator--(Direction &dir) {
    dir -= 1;
    return dir;
}

const Direction operator++(Direction &dir, int) {
    Direction ret(dir);
    ++dir;
    return ret;
}

const Direction operator--(Direction &dir, int) {
    Direction ret(dir);
    --dir;
    return ret;
}
