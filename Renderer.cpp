//
// Created by zeroji on 2/23/18.
//

#include <iostream>
#include "Renderer.hpp"
#include "Player.hpp"

Renderer::Renderer(const ResourceLoader &res, Engine *engine, sf::RenderTarget *target) :
        res(res), engine(engine), target(target), map(engine->getMap()),
        width(map.getWidth()), height(map.getHeight())
{
    // View is technically one pixel per tile, scaled by viewport
    gameView.reset(sf::FloatRect(0, 0, width, height));
    sf::Vector2f size(target->getSize());
    float borderLeft = (size.x - width * tileSize) / 2.f, borderTop = (size.y - height * tileSize) / 2.f;
    gameView.setViewport(sf::FloatRect(borderLeft / size.x, borderTop / size.y, width *tileSize / size.x, height * tileSize / size.y));

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
    playerSpr.setTexture(res.player);
    const sf::Vector2f pTSize(res.player.getSize());
    playerSpr.setScale(1 / pTSize.x, 1 / pTSize.y);
    playerSpr.setOrigin(pTSize / 2.f);

}

// Some default colors for players. Useful to differentiate.
const std::vector<sf::Color> Renderer::defaultColors = {
        sf::Color::Blue, sf::Color::Magenta, sf::Color::Green, sf::Color::Red, sf::Color::Cyan
};

void Renderer::render() {
    target->setView(gameView);

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

    target->draw(vertices, &res.tiles);

    for(const Player &p: engine->getPlayers()) {
        playerSpr.setColor(defaultColors[p.id]);
        // Add 1, 1 to account for origin translation, divide to account for half tiles
        playerSpr.setPosition((p.getIPos() + sf::Vector2f(1, 1)) / 2.f);
        playerSpr.setRotation(p.facing * 90.f);
        target->draw(playerSpr);
    }
}
