//
// Created by zeroji on 2/24/18.
//

#include "Player.hpp"

Player::Player(const sf::Vector2u &pos, const unsigned int &id) : Entity(pos), id(id) {
    bombCount = 3;
    bombRange = 1;
    shield = false;
    speed = sf::milliseconds(200/TSZ);
}

void Player::move(const Direction &dir) {
    facing = dir;
    moving = true;
}
