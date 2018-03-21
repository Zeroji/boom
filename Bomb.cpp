//
// Created by zeroji on 3/12/18.
//

#include "Bomb.hpp"

Bomb::Bomb(const sf::Vector2u &pos) : Entity(pos), state(BombState::TICK) {}

bool Bomb::update(const sf::Time &elapsed) {
    if(state == BombState::DONE) return false;
    bool changed = false;
    oldRadius = radius;
    tick += elapsed;
    if(state == BombState::TICK) {
        if(tick >= tickDelay) {
            tick -= tickDelay;
            tickRatio = 1;
            state = BombState::EXPLODING;
            changed = true;
        } else {
            tickRatio = tick / tickDelay;
        }
    }
    if(state == BombState::EXPLODING) {
        radius = std::min(explosionMaxRadius, (unsigned int)(tick / explosionSpeed));
        if(tick > (float) explosionMaxRadius * explosionSpeed + explosionFinalDelay) {
            state = BombState::DONE;
            changed = true;
        }
    }
    return changed || oldRadius != radius;
}

void Bomb::detonate() {
    if(state == BombState::TICK) {
        tickRatio = 1;
        tick = tickDelay;
    }
}
