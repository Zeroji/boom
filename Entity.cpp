//
// Created by zeroji on 2/24/18.
//

#include <iostream>
#include "Entity.hpp"
#include "Engine.hpp"

Entity::Entity(const sf::Vector2u &pos) : pos(pos), old(pos), cooldown(sf::Time::Zero) {}

void Entity::moveTo(sf::Vector2u newPos) {
    old = pos;
    pos = newPos;
    cooldown = sf::Time::Zero;
}

void Entity::updateClock(sf::Time elapsed) {
    cooldown += elapsed;
}

const sf::Vector2u &Entity::getPos() const {
    return pos;
}

sf::Vector2f Entity::getIPos() const {
    if(cooldown > speed || old == pos) {
        return sf::Vector2f(pos);
    } else {
        float ratio = cooldown / speed;
        return sf::Vector2f(pos) * ratio + sf::Vector2f(old) * (1 - ratio);
    }
}
