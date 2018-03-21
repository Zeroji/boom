//
// Created by zeroji on 3/12/18.
//

#ifndef BOOM_BOMB_HPP
#define BOOM_BOMB_HPP


#include "Entity.hpp"

enum class BombState { TICK, EXPLODING, DONE };

class Bomb : public Entity {
public:
    explicit Bomb(const sf::Vector2u &pos);

    /**
     * Updates the bomb
     * @param elapsed elapsed time
     * @return true if the bomb changed
     */
    bool update(const sf::Time &elapsed);

    /**
     * Detonates the bomb next update
     */
    void detonate();

    BombState state;
    float tickRatio=0;
    unsigned int radius=0, oldRadius=0;

private:
    sf::Time tick=sf::Time::Zero;
    sf::Time tickDelay=sf::milliseconds(2000);
    sf::Time explosionSpeed=sf::milliseconds(200);
    sf::Time explosionFinalDelay=sf::milliseconds(1000);
    unsigned int explosionMaxRadius=3;
};


#endif //BOOM_BOMB_HPP
