//
// Created by zeroji on 3/6/18.
//

#include "PlayerMenu.hpp"

PlayerMenu::PlayerMenu(const ResourceLoader &res, PlayerSkin *skin) : res(res), name(3) {
    outline.setSize(sf::Vector2f(78, 58));
    outline.setPosition(1, 1);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineThickness(1);

    for(unsigned int i=0; i<3; i++) {
        sf::Text &letter = name[i];
        letter.setFont(res.font);
        letter.setPosition(i * 20 + 3, 6);
        letter.setFillColor(sf::Color::White);
        letter.setCharacterSize(17);
    }

    setSkin(skin);
}

void PlayerMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(outline, states);
    for(auto &letter: name)
        target.draw(letter, states);
}

void PlayerMenu::setSkin(PlayerSkin *skin) {
    PlayerMenu::skin = skin;
    outline.setOutlineColor(skin?skin->color:sf::Color(128, 128, 128));
    std::string text(skin ? skin->name : "?  ");
    for (unsigned int i = 0; i < 3; ++i) {
        name[i].setString(text[i]);
        name[i].setFillColor(skin ? sf::Color::White : sf::Color(128, 128, 128));
    }
}
