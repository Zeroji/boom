//
// Created by zeroji on 3/6/18.
//

#include "PlayerSkin.hpp"

const std::vector<sf::Color> PlayerSkin::colors = {
        sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow,
        sf::Color::Cyan, sf::Color(255, 128, 0), sf::Color::Magenta, sf::Color(192, 192, 192)
};

PlayerSkin::PlayerSkin(unsigned int id) : color(id % (unsigned int) colors.size()) {}

const sf::Color &PlayerSkin::getColor() const {
    return colors[color];
}

const sf::Color &PlayerSkin::getColor(int delta) const {
    int index = (int) color + delta;
    while (index < 0) index += (int) colors.size();
    return colors[index % colors.size()];
}

void PlayerSkin::setColor(int delta) {
    int index = (int) color + delta;
    while (index < 0) index += (int) colors.size();
    color = (unsigned int)(index % colors.size());
}
