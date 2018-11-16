//
// Created by zeroji on 3/12/18.
//

#ifndef BOOM_BOMB_HPP
#define BOOM_BOMB_HPP


class Player;
#include "Entity.hpp"

enum class BombState { TICK, EXPLODING, DONE };

class Bomb : public Entity {
public:
    explicit Bomb(const sf::Vector2u &pos, const Player *player = nullptr);

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

    BombState state, oldState;
    float tickRatio;
    unsigned int radius, oldRadius;
    const Player *player;

private:
    sf::Time tick;
    sf::Time tickDelay;
    sf::Time explosionSpeed;
    sf::Time explosionFinalDelay;
    unsigned int explosionMaxRadius;
};


#endif //BOOM_BOMB_HPP
