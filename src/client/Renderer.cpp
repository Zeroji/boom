//
// Created by zeroji on 2/23/18.
//

#include <iostream>
#include "core/Player.hpp"
#include "Renderer.hpp"

const sf::Vector2f ONE(1.f, 1.f);

Renderer::Renderer(const ResourceLoader &res, Engine *engine, sf::RenderTarget *target, const std::vector<PlayerSkin*> &skins) :
        px(16), pxScale(ONE / (float) px), pxOrigin(px / 2.f, px / 2.f),
        res(res), engine(engine), target(target), skins(skins), map(engine->getMap()),
        width(map.getWidth()), height(map.getHeight()), defaultExplosionColor(sf::Color::Red)
{
    // View is technically one pixel per tile, scaled by viewport
    gameView.reset(sf::FloatRect(0, 0, width, height));
    sf::Vector2f size(target->getSize());
    float borderLeft = (size.x - width * px) / 2.f, borderTop = (size.y - height * px) / 2.f;
    gameView.setViewport(sf::FloatRect(borderLeft / size.x, borderTop / size.y, width *px / size.x, height * px / size.y));

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
    playerSpr.setScale(pxScale);
    playerSpr.setOrigin(pxOrigin);

    bombSpr.setTexture(res.bomb);
    bombSpr.setScale(pxScale);

    explosion.setTexture(res.explosion);
    explosion.setScale(pxScale);
    explosion.setColor(sf::Color::Red);

    upgrade.setTexture(res.upgrades);
    upgrade.setScale(pxScale);
}

void Renderer::render() {
    target->setView(gameView);

    // Set textures for vertices
    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            unsigned int i = (y * width + x) * 4;
            auto t = (unsigned int) map(x, y);
            vertices[i+0].texCoords = sf::Vector2f(t*px, 0);
            vertices[i+1].texCoords = sf::Vector2f(t*px+px, 0);
            vertices[i+2].texCoords = sf::Vector2f(t*px+px, px);
            vertices[i+3].texCoords = sf::Vector2f(t*px, px);
        }
    }

    target->draw(vertices, &res.tiles);

    // Draw upgrades
    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            const Upgrade *up = map.getUpgrade({x, y});
            if(up != nullptr) {
                upgrade.setPosition(x, y);
                upgrade.setTextureRect(sf::IntRect((int)up->type*16, 0, 16, 16));
                target->draw(upgrade);
            }
        }
    }

    for(const Player &p: engine->getPlayers()) {
        skins[p.id]->applyTo(playerSpr, p.facing);
        // Divide to account for tile fractions, then add (.5, .5) to account for origin translation
        playerSpr.setPosition(p.getIPos() / (float)TSZ + ONE/2.f);
        target->draw(playerSpr);
    }

    for(const auto &bomb: engine->getBombs()) {
        if(bomb->state == BombState::TICK) {
            bombSpr.setPosition(bomb->getIPos() / (float)TSZ);
            target->draw(bombSpr);
        }
    }

    // Draw bomb explosions
    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            auto const &bombs = map.getBombs(sf::Vector2u(x, y));
            if (!bombs.empty()) {
                explosion.setPosition(x, y);
                for(auto const &bomb: bombs) {
                    unsigned int k = 0;  // ID of texture to apply
                    if(bomb->pos / TSZ == sf::Vector2u(x, y)) k=15;
                    else {
                        /**
                         * Takes a position in parameter
                         * Returns true if that position contains an explosion from the same player
                         */
                        auto hasSameBomb = [this, bomb](unsigned int x, unsigned int y) -> bool {
                            auto const &bs = map.getBombs(sf::Vector2u(x, y));
                            for (auto const &b: bs)
                                if (b->player == bomb->player)
                                    return true;
                            return false;
                        };
                        // Change texture ID according to nearby bombs of same color
                        if (hasSameBomb(x + 1, y)) k += 1;
                        if (hasSameBomb(x, y + 1)) k += 2;
                        if (hasSameBomb(x - 1, y)) k += 4;
                        if (hasSameBomb(x, y - 1)) k += 8;
                    }
                    explosion.setTextureRect(sf::IntRect(k*16, 0, 16, 16));
                    explosion.setColor(getExplosionColor(*bomb));
                    target->draw(explosion);
                }
            }
        }
    }
}

const sf::Color &Renderer::getExplosionColor(const Bomb &bomb) const {
    if(bomb.player == nullptr)
        return defaultExplosionColor;
    else
        return skins[bomb.player->id]->getColor();
}
