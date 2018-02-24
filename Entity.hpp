//
// Created by zeroji on 2/24/18.
//

#ifndef BOOM_ENTITY_HPP
#define BOOM_ENTITY_HPP
class Engine;

#include "Engine.hpp"
#include <SFML/System.hpp>

class Entity {
public:
    Entity(const Engine *engine, const sf::Vector2u &pos);
    void moveTo(sf::Vector2u newPos);

public:
    const Engine *engine;
    sf::Vector2u pos;
};


#endif //BOOM_ENTITY_HPP
