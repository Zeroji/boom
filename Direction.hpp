//
// Created by zeroji on 2/26/18.
//

#ifndef BOOM_DIRECTION_HPP
#define BOOM_DIRECTION_HPP


#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

/**
 * Lists the different directions, NONE should not be a stored value
 */
enum Direction : int8_t {
    UP=3, DOWN=1, LEFT=2, RIGHT=0, NONE=-1
};

/**
 * Offset a position by one in a certain direction
 * @param pos The original position
 * @param dir The offset direction
 * @return The new position
 */
sf::Vector2u operator+(const sf::Vector2u &pos, const Direction &dir);
sf::Vector2u &operator+=(sf::Vector2u &pos, const Direction &dir);

#endif //BOOM_DIRECTION_HPP
