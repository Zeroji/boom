//
// Created by zeroji on 3/6/18.
//

#include "PlayerMenu.hpp"

PlayerMenu::PlayerMenu(sf::Font &font, PlayerSkin *skin) : font(font) {
    outline.setSize(sf::Vector2f(78, 58));
    outline.setPosition(1, 1);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineThickness(1);

    name.setFont(font);
    name.setPosition(3, 1);
    name.setFillColor(sf::Color::White);
    name.setCharacterSize(17);

    setSkin(skin);
}

void PlayerMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(outline, states);
    target.draw(name, states);
}

void PlayerMenu::setSkin(PlayerSkin *skin) {
    PlayerMenu::skin = skin;
    outline.setOutlineColor(skin?skin->color:sf::Color(128, 128, 128));
    name.setString(skin ? skin->name : "?");
    name.setFillColor(skin ? sf::Color::White : sf::Color(128, 128, 128));
}
