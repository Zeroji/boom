//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_RENDERER_HPP
#define BOOM_RENDERER_HPP


#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "Player.hpp"

/**
 * Draws the state of a game engine to a window
 */
class Renderer {
public:
    Renderer(Engine *engine, sf::RenderTarget *target);

    void render();

private:
    static const std::vector<sf::Color> defaultColors;
    const unsigned int tileSize = 16;
    sf::Texture tileSet;
    sf::VertexArray vertices;
    sf::Texture playerTex;
    sf::Sprite playerSpr;

    Engine *engine;
    const Map &map;
    const unsigned int width, height;
    sf::RenderTarget *target;
    sf::View gameView;
};


#endif //BOOM_RENDERER_HPP
