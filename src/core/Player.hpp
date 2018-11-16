//
// Created by zeroji on 2/24/18.
//

#ifndef BOOM_PLAYER_HPP
#define BOOM_PLAYER_HPP

#include <SFML/System.hpp>
#include "Entity.hpp"
#include "Direction.hpp"

class Player : public Entity {
public:
    Player(const sf::Vector2u &pos, const unsigned int &id);
    void move(const Direction &dir);
    inline void stop() { moving = false; }

    const unsigned int id;
    Direction facing = NONE;
    Direction facing2 = NONE;
    bool moving;

    unsigned int bombCount;
    unsigned int bombRange;
    bool shield;
};


#endif //BOOM_PLAYER_HPP
