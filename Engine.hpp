//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_ENGINE_HPP
#define BOOM_ENGINE_HPP

#include <cstdint>

class Entity;
enum class Control : int8_t;

#include "Map.hpp"
#include "Player.hpp"
#include "Bomb.hpp"

class Engine {
public:
    Engine(const unsigned int &mapWidth, const unsigned int &mapHeight, const unsigned int &playerCount);

    bool moveEntity(Entity &entity, const sf::Vector2u &pos);
    bool updatePlayer(Player &player);
    bool updateBomb(const Bomb *bomb);
    void apply(Player &player, const UpType &upgrade);

    const Map &getMap() const;

    inline bool isBlocking(sf::Vector2u &pos) const { return tile::isBlocking(map(pos)); }
    inline bool isSurface(sf::Vector2u &pos) const { return tile::isSurface(map(pos)); }
    inline bool isBreakable(sf::Vector2u &pos) const { return tile::isBreakable(map(pos)); }

    bool isValid(const sf::Vector2u &entityPos) const;

    void update(const sf::Time &elapsed);
    const std::vector<Player> &getPlayers() const;
    const std::vector<std::unique_ptr<Bomb>> &getBombs() const;
    void processInput(const unsigned int &playerId, const Control &control, const bool &state, const std::vector<Control> &controls);

private:
    Map map;
    unsigned int playerCount;
    std::vector<Player> players;
    std::vector<std::unique_ptr<Bomb>> bombs;
};


#endif //BOOM_ENGINE_HPP
