//
// Created by zeroji on 2/23/18.
//

#include "Engine.hpp"
#include "Control.hpp"

Engine::Engine(const unsigned int &mapWidth, const unsigned int &mapHeight, const unsigned int &playerCount):
        map(mapWidth, mapHeight), playerCount(playerCount) {
    for (unsigned int i = 0; i < playerCount; ++i) {
        Player player(map.getPlayerBase(i) * TSZ, i);
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
    for(const auto &bomb: bombs)
        if(bomb->getPos() == entityPos) return false;
    checks.push_back(entityPos / TSZ);
    if(entityPos.x % TSZ > 0) checks.emplace_back(sf::Vector2u(entityPos.x / TSZ + 1, entityPos.y / TSZ));
    if(entityPos.y % TSZ > 0) checks.emplace_back(entityPos.x / TSZ, entityPos.y / TSZ + 1);
    if(entityPos.x % TSZ > 0 && entityPos.y % TSZ > 0) checks.emplace_back(entityPos.x / TSZ + 1, entityPos.y / TSZ + 1);
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

const std::vector<std::unique_ptr<Bomb>> &Engine::getBombs() const {
    return bombs;
}

void Engine::processInput(const unsigned int &playerId, const Control &control, const bool &state, const std::vector<Control> &controls) {
    if(playerId >= playerCount) return;
    Player &player = players[playerId];
    Direction d = control::toDir(control);
    if(d != NONE) {
        // We have a (potential) direction update
        player.stop();
        bool first = true;
        player.facing2 = NONE;
        for(const Control &c: controls) {
            if(control::isDir(c)) {
                if(first) {
                    player.move(control::toDir(c));
                    first = false;
                } else {
                    player.facing2 = control::toDir(c);
                    break;
                }
            }
        }
    }
    if(control == Control::A && state && player.bombCount > 0) {
        bool place = true;
        for(auto const &bomb: bombs)
            if(bomb->getPos() == player.getLastTiledPos())
                place = false;
        if(place) {
            bombs.emplace_back(new Bomb(player.getLastTiledPos(), &player));
            --player.bombCount;
        }
    }
}

void Engine::update(const sf::Time &elapsed) {
    for(Player &player: players) {
        updatePlayer(player);
        player.updateClock(elapsed);
    }
    for (int i = 0; i < bombs.size(); ++i) {
        auto &bomb = bombs[i];
        if(bomb->update(elapsed)) {
            updateBomb(bomb.get());
            if(bomb->oldState != BombState::EXPLODING && bomb->state == BombState::EXPLODING) {
                // Make bomb usable again right after detonation
                players[bomb->player->id].bombCount++;
            } else if (bomb->state == BombState::DONE) {
                map.removeBomb(bomb.get());
                bombs.erase(bombs.begin() + i);
                --i;
            }
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
    else {
        if(!moveEntity(player, player.pos + player.facing)) {
            bool moved = false;
            // If player can't move forward, check to their left/right for valid spots forward
            const Direction forward = player.facing, left = forward - 1, right = forward + 1;
            if(isValid(player.pos >> left) && isValid((player.pos >> left) + forward)) {
                moved |= moveEntity(player, player.pos + left);
            } else if(isValid(player.pos >> right) && isValid((player.pos >> right) + forward)) {
                moved |= moveEntity(player, player.pos + right);
            }
            if(!moved  && player.facing2 != NONE)
                moved |= moveEntity(player, player.pos + player.facing2);
            if(!moved)
                return false;
        }
        // perform post-movement checks
        const unsigned int x = player.pos.x, y = player.pos.y;
        if(player.pos.x % TSZ == 0 && player.pos.y % TSZ == 0) {
            const Upgrade *upgrade = map.getUpgrade(player.pos / TSZ);
            if(upgrade != nullptr) {
                apply(player, upgrade->type);
                map.removeUpgrade(player.pos / TSZ);
            }
        }
        return true;
    }
}

bool Engine::updateBomb(const Bomb *bomb) {
    static const Direction dirs[4] = {UP, DOWN, LEFT, RIGHT};
    if(bomb->oldState == BombState::TICK && bomb->state == BombState::EXPLODING)
        map.updateBomb(bomb, bomb->pos / TSZ, 0);
    if(bomb->oldRadius != bomb->radius && bomb->state == BombState::EXPLODING) {
        for(const Direction &dir: dirs) {
            sf::Vector2u pos(bomb->pos / TSZ);
            for (unsigned int i = 1; i <= bomb->radius; ++i) {
                pos += dir;
                if(isBlocking(pos) && !isBreakable(pos))
                    break;
                if(i > bomb->oldRadius) {
                    // Break blocks
                    if (isBreakable(pos))
                        if(!map.breakTile(pos))
                            break;
                    // Tile newly reached by explosion radius
                    map.updateBomb(bomb, pos, i);
                    // Detonate nearby bombs
                    for(auto &b: bombs) {
                        if(b->getPos() / TSZ == pos)
                            b->detonate();
                    }
                }
            }
        }
    }
}

void Engine::apply(Player &player, const UpType &upgrade) {
    switch (upgrade) {
        case UpType::BOMB_COUNT:
            ++player.bombCount;
            break;
        case UpType::BOMB_RANGE:
            ++player.bombRange;
            break;
        case UpType::SPEED:
            player.speed -= sf::milliseconds(10);
            break;
        case UpType::SHIELD:
            player.shield = true;
            break;
    }
}
