//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_RENDERER_HPP
#define BOOM_RENDERER_HPP


#include <SFML/Graphics.hpp>
#include "Engine.hpp"

/**
 * Draws the state of a game engine to a window
 */
class Renderer {
public:
    Renderer(Engine *engine, sf::RenderWindow *window);

    void render();
    void resize(unsigned int width, unsigned int height);

private:
    const unsigned int tileSize = 16;
    sf::Texture tileSet;
    sf::VertexArray vertices;

    Engine *engine;
    const Map &map;
    const unsigned int width, height;
    sf::RenderWindow *window;
    sf::View gameView;
};


#endif //BOOM_RENDERER_HPP