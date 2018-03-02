//
// Created by zeroji on 2/23/18.
//

#include <iostream>
#include "Renderer.hpp"
#include "Player.hpp"

Renderer::Renderer(Engine *engine, sf::RenderWindow *window) :
        engine(engine), window(window), map(engine->getMap()),
        width(map.getWidth()), height(map.getHeight())
{
    tileSet.loadFromFile("res/tiles.png");

    // View is technically one pixel per tile, scaled by viewport
    gameView.reset(sf::FloatRect(0, 0, width, height));

    // Initialize vertex array and fill positions (tiles won't move)
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(width * height * 4);
    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            unsigned int i = (y * width + x) * 4;
            vertices[i+0].position = sf::Vector2f(x  , y  );
            vertices[i+1].position = sf::Vector2f(x+1, y  );
            vertices[i+2].position = sf::Vector2f(x+1, y+1);
            vertices[i+3].position = sf::Vector2f(x  , y+1);
        }
    }

    // Initialize player view
    playerTex.loadFromFile("res/player.png");
    playerSpr.setTexture(playerTex);
    const sf::Vector2f pTSize(playerTex.getSize());
    playerSpr.setScale(1 / pTSize.x, 1 / pTSize.y);
    playerSpr.setOrigin(pTSize / 2.f);

}

// Some default colors for players. Useful to differentiate.
const std::vector<sf::Color> Renderer::defaultColors = {
        sf::Color::Blue, sf::Color::Magenta, sf::Color::Green, sf::Color::Red, sf::Color::Cyan
};

void Renderer::render() {
    window->setView(gameView);

    // Set textures for vertices
    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            unsigned int i = (y * width + x) * 4;
            unsigned int t = map(x, y);
            vertices[i+0].texCoords = sf::Vector2f(t*tileSize, 0);
            vertices[i+1].texCoords = sf::Vector2f(t*tileSize+tileSize, 0);
            vertices[i+2].texCoords = sf::Vector2f(t*tileSize+tileSize, tileSize);
            vertices[i+3].texCoords = sf::Vector2f(t*tileSize, tileSize);
        }
    }

    window->draw(vertices, &tileSet);

    for(const Player &p: engine->getPlayers()) {
        playerSpr.setColor(defaultColors[p.id]);
        // Add 1, 1 to account for origin translation, divide to account for half tiles
        playerSpr.setPosition((p.getIPos() + sf::Vector2f(1, 1)) / 2.f);
        playerSpr.setRotation(p.facing * 90.f);
        window->draw(playerSpr);
    }
}

/**
 * Creates a letterbox view to keep the engine aspect ratio,
 * no matter what the window aspect ratio is set to
 * @param width Window width
 * @param height Window height
 */
void Renderer::resize(unsigned int width, unsigned int height) {
    float windowRatio = width / (float) height;
    float engineRatio = this->width / (float) this->height;

    sf::FloatRect viewport(0, 0, 1.f, 1.f);
    if(windowRatio > engineRatio) {             // Horizontal black bars
        viewport.width = engineRatio / windowRatio;
        viewport.left = (1 - viewport.width) / 2;
    } else {                                    // Vertical black bars
        viewport.height = windowRatio / engineRatio;
        viewport.top = (1 - viewport.height) / 2;
    }
    gameView.setViewport(viewport);
}
