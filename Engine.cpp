//
// Created by zeroji on 2/23/18.
//

#include "Engine.hpp"
#include "Control.hpp"

Engine::Engine(const unsigned int &mapWidth, const unsigned int &mapHeight, const unsigned int &playerCount):
        map(mapWidth, mapHeight), playerCount(playerCount) {
    for (unsigned int i = 0; i < playerCount; ++i) {
        Player player(sf::Vector2u(4 * i + 2, 2), i);
        players.emplace_back(player);
    }
}

const Map &Engine::getMap() const {
    return map;
}

bool Engine::isValid(const sf::Vector2u &entityPos) const {
    std::vector<sf::Vector2u> checks;
    for(const auto &player: players)
        if(player.getPos() == entityPos) return false;
    checks.push_back(entityPos / 2u);
    if(entityPos.x % 2 == 1) checks.emplace_back(sf::Vector2u(entityPos.x / 2u + 1, entityPos.y / 2u));
    if(entityPos.y % 2 == 1) checks.emplace_back(entityPos.x / 2u, entityPos.y / 2u + 1);
    if(entityPos.x % 2 == 1 && entityPos.y % 2 == 1) checks.emplace_back(entityPos.x / 2u + 1, entityPos.y / 2u + 1);
    bool surface = false;
    for(auto &pos: checks) {
        if (isBlocking(pos))
            return false;
        if (isSurface(pos))
            surface = true;
    }
    return surface;
}

const std::vector<Player> &Engine::getPlayers() const {
    return players;
}

const std::vector<Bomb> &Engine::getBombs() const {
    return bombs;
}

void Engine::processInput(const unsigned int &playerId, const Control &control, const bool &state, const std::vector<Control> &controls) {
    if(playerId >= playerCount) return;
    Player &player = players[playerId];
    Direction d = control::toDir(control);
    if(d != NONE) {
        // We have a (potential) direction update
        player.stop();
        for(const Control &c: controls) {
            if(control::isDir(c)) {
                player.move(control::toDir(c));
                break;
            }
        }
    }
    if(control == Control::A && state) {
        bombs.emplace_back(Bomb(player.getLastEvenPos()));
    }
}

void Engine::update(const sf::Time &elapsed) {
    for(Player &player: players) {
        updatePlayer(player);
        player.updateClock(elapsed);
    }
    for (int i = 0; i < bombs.size(); ++i) {
        Bomb &bomb = bombs[i];
        bomb.update(elapsed);
        if(bomb.state == BombState::DONE) {
            bombs.erase(bombs.begin() + i);
            --i;
        }
    }
}

bool Engine::moveEntity(Entity &entity, const sf::Vector2u &pos) {
    if(isValid(pos)) {
        entity.moveTo(pos);
        return true;
    }
    return false;
}

bool Engine::updatePlayer(Player &player) {
    if(!player.moving)
        return false;
    if(player.cooldown < player.speed)
        return false;
    else
        return moveEntity(player, player.pos + player.facing);
}
