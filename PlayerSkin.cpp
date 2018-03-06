//
// Created by zeroji on 3/6/18.
//

#include "PlayerSkin.hpp"

const std::vector<sf::Color> PlayerSkin::defaultColors = {
        sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow,
        sf::Color::Cyan, sf::Color(255, 128, 0), sf::Color::Yellow, sf::Color(192, 192, 192)
};

PlayerSkin::PlayerSkin(unsigned int id) {
    color = defaultColors[id % defaultColors.size()];
}
