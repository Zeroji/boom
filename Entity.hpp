//
// Created by zeroji on 2/24/18.
//

#ifndef BOOM_ENTITY_HPP
#define BOOM_ENTITY_HPP

#include <SFML/System.hpp>

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

public:
    sf::Vector2u old, pos;
    sf::Time speed;
    sf::Time cooldown;
};


#endif //BOOM_ENTITY_HPP
