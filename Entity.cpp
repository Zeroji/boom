//
// Created by zeroji on 2/24/18.
//

#include "Entity.hpp"

Entity::Entity(const Engine *engine, const sf::Vector2u &pos) : engine(engine), pos(pos) {}

void Entity::moveTo(sf::Vector2u newPos) {
    if(engine->isValid(newPos))
        pos = newPos;
}
