//
// Created by zeroji on 2/23/18.
//

#include <iostream>
#include "Renderer.hpp"
#include "Player.hpp"

Renderer::Renderer(const ResourceLoader &res, Engine *engine, sf::RenderTarget *target, const std::vector<PlayerSkin*> &skins) :
        res(res), engine(engine), target(target), skins(skins), map(engine->getMap()),
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

    bombSpr.setTexture(res.bomb);
    const sf::Vector2f bTSize(res.bomb.getSize());
    bombSpr.setScale(1 / bTSize.x, 1 / bTSize.y);
    bombSpr.setOrigin(bTSize / 2.f);

    bombTxt.setFont(res.font);
    bombTxt.setCharacterSize(17);
    bombTxt.setScale(sf::Vector2f(1/16.f, 1/16.f));
    bombTxt.setFillColor(sf::Color::Green);

}

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
        skins[p.id]->applyTo(playerSpr, p.facing);
        // Add 1, 1 to account for origin translation, divide to account for half tiles
        playerSpr.setPosition((p.getIPos() + sf::Vector2f(1, 1)) / 2.f);
        target->draw(playerSpr);
    }

    for(const Bomb &b: engine->getBombs()) {
        bombSpr.setPosition((b.getIPos() + sf::Vector2f(1, 1)) / 2.f);
        bombTxt.setPosition(bombSpr.getPosition());
        if(b.state == BombState::TICK) bombTxt.setString(std::to_string(b.tickRatio));
        else bombTxt.setString(std::to_string(b.radius));
        target->draw(bombSpr);
        target->draw(bombTxt);
    }
}
