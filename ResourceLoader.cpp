//
// Created by zeroji on 3/6/18.
//

#include "ResourceLoader.hpp"
#include <iostream>

sf::Texture ResourceLoader::loadTexture(const std::string &path, const std::string &filename) {
    sf::Texture temp;
    if (!temp.loadFromFile(path + "/" + filename)) {
        std::cerr << "Couldn't load texture file: " << path + "/" + filename << std::endl;
    }
    return temp;
}

sf::Font ResourceLoader::loadFont(const std::string &path, const std::string &filename) {
    sf::Font temp;
    if (!temp.loadFromFile(path + "/" + filename)) {
        std::cerr << "Couldn't load font file: " << path + "/" + filename << std::endl;
    }
    return temp;
}

ResourceLoader::ResourceLoader(const std::string &path) :
        tiles(loadTexture(path, "tiles.png")),
        player(loadTexture(path, "player.png")),
        arrow(loadTexture(path, "arrow.png")),
        bomb(loadTexture(path, "bomb.png")),
        font(loadFont(path, "04b_30.ttf"))
{
}
