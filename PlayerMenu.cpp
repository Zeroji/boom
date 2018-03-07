//
// Created by zeroji on 3/6/18.
//

#include "PlayerMenu.hpp"

PlayerMenu::PlayerMenu(const ResourceLoader &res, PlayerSkin *skin) : res(res), skin(skin), name(3), letterIndex(0), state(MenuState::NAME) {
    outline.setSize(sf::Vector2f(78, 58));
    outline.setPosition(1, 1);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineThickness(1);

    for(unsigned int i=0; i<3; i++) {
        sf::Text &letter = name[i];
        letter.setFont(res.font);
        letter.setPosition(i * 20 + 10, 4);
        letter.setFillColor(sf::Color::White);
        letter.setCharacterSize(17);
    }

    sf::Sprite *arrows[] = {&arrowUp, &arrowDown};
    for(sf::Sprite *arrow: arrows) {
        arrow->setTexture(res.arrow);
        arrow->setOrigin(2, 4);
    }

    arrowUp.setPosition(10, 4);
    arrowUp.setRotation(-90);
    arrowDown.setPosition(10, 24);
    arrowDown.setRotation(90);

    update();
}

void PlayerMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(outline, states);
    for(auto &letter: name)
        target.draw(letter, states);
    if(skin && state == MenuState::NAME) {
        target.draw(arrowUp, states);
        target.draw(arrowDown, states);
    }
}

void PlayerMenu::setSkin(PlayerSkin *skin) {
    PlayerMenu::skin = skin;
    update();
}

void PlayerMenu::update() {
    sf::Color main = skin ? skin->color : sf::Color(128, 128, 128);
    outline.setOutlineColor(main);
    std::string text(skin ? skin->name : "?  ");
    for (unsigned int i = 0; i < 3; ++i) {
        name[i].setString(text[i]);
        name[i].setFillColor(skin ? sf::Color::White : sf::Color(128, 128, 128));
        name[i].setOrigin(std::min((int)(name[i].getGlobalBounds().width+1)/2u, 7u), 0);  // Center glyphs
    }
    arrowUp.setPosition(20*letterIndex+10, 4);
    arrowDown.setPosition(20*letterIndex+10, 24);
    arrowUp.setColor(main);
    arrowDown.setColor(main);
}

void PlayerMenu::keyPressed(const Control &control) {
    if(!skin) return;
    char &l = skin->name[letterIndex];
    switch (state) {
        case MenuState::NAME:
            switch (control) {
                case Control::Down:
                    if(l=='Z') l=' ';
                    else if(l==' ') l='A';
                    else l++;
                    break;
                case Control::Up:
                    if(l=='A') l=' ';
                    else if(l==' ') l='Z';
                    else l--;
                    break;
                case Control::Left:
                    if(letterIndex>0) letterIndex--;
                    break;
                case Control::Right:
                    if(letterIndex<2) letterIndex++;
                    break;
                default: break;
            }
            break;
    }
    update();
}
