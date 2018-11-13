//
// Created by zeroji on 2/24/18.
//

#ifndef BOOM_ENTITY_HPP
#define BOOM_ENTITY_HPP

#include <SFML/System.hpp>
#include "Direction.hpp"

// Tile fraction size, i.e. how precisely can you stand between two tiles
// 1u is full tiles, 2u is half-tiles (legacy default)
#define TSZ 4u

class Entity {
public:
    explicit Entity(const sf::Vector2u &pos);

    void moveTo(sf::Vector2u newPos);

    /**
     * Update the internal clock (time since last move)
     * @param elapsed Elapsed time
     */
    void updateClock(sf::Time elapsed);

    /**
     * Return entity real position
     * @return Entity position
     */
    const sf::Vector2u &getPos() const;

    /**
     * Return entity interpolated position (same domain)
     * @return Entity interpolated position (or real if not moving)
     */
    sf::Vector2f getIPos() const;

    /**
     * Return entity last even (full-tile) position
     * @return Last even position
     */
    const sf::Vector2u &getLastTiledPos() const;

public:
    sf::Vector2u old, pos, lastTiledPos;
    sf::Time speed;
    sf::Time cooldown;
};

/**
 * Shift a position in a direction until it's grid-aligned (on that axis)
 * @param pos The original position
 * @param dir The shift direction
 * @return The grid-aligned position
 */
sf::Vector2u operator>>(const sf::Vector2u &pos, const Direction &dir);

#endif //BOOM_ENTITY_HPP
