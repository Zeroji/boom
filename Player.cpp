//
// Created by zeroji on 2/24/18.
//

#include "Player.hpp"

Player::Player(const sf::Vector2u &pos, const unsigned int &id) : Entity(pos), id(id) {
    speed = sf::milliseconds(80);
}

void Player::move(const Direction &dir) {
    facing = dir;
    moving = true;
}
