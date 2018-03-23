//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_RENDERER_HPP
#define BOOM_RENDERER_HPP


#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "Player.hpp"
#include "ResourceLoader.hpp"
#include "PlayerSkin.hpp"

/**
 * Draws the state of a game engine to a window
 */
class Renderer {
public:
    Renderer(const ResourceLoader &res, Engine *engine, sf::RenderTarget *target,
                 const std::vector<PlayerSkin *> &skins);

    void render();

private:
    const ResourceLoader &res;

    const unsigned int px;  // pixel art size (probably 16x16)
    const sf::Vector2f pxScale, pxOrigin;
    sf::VertexArray vertices;
    sf::Sprite playerSpr;
    sf::Sprite bombSpr;

    Engine *engine;
    const Map &map;
    const std::vector<PlayerSkin*> skins;
    const unsigned int width, height;
    sf::RenderTarget *target;
    sf::View gameView;

    sf::Sprite explosion;
    sf::Color defaultExplosionColor;

    const sf::Color &getExplosionColor(const Bomb &bomb) const;
};


#endif //BOOM_RENDERER_HPP
