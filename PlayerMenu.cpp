//
// Created by zeroji on 3/6/18.
//

#include "PlayerMenu.hpp"

const sf::Color PlayerMenu::noColor(128, 128, 128);
const sf::Color PlayerMenu::leaveColor(160, 64, 64);

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

    sf::Sprite *arrows[] = {&arrowUp, &arrowDown, &colorArrow, &leaveArrow};
    for(sf::Sprite *arrow: arrows) {
        arrow->setTexture(res.arrow);
        arrow->setOrigin(2, 4);
    }

    arrowUp.setPosition(10, 4);
    arrowUp.setRotation(-90);
    arrowDown.setPosition(10, 24);
    arrowDown.setRotation(90);

    colorText.setString("color");
    colorText.setFont(res.font);
    colorText.setPosition(3, 24);
    colorText.setCharacterSize(17);

    colorArrow.setPosition(74, 35);

    leaveText.setString("leave");
    leaveText.setFont(res.font);
    leaveText.setPosition(3, 39);
    leaveText.setCharacterSize(17);

    leaveArrow.setRotation(180);
    leaveArrow.setPosition(74, 50);
    leaveArrow.setColor(leaveColor);

    update();
}

void PlayerMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(outline, states);
    for(auto &letter: name)
        target.draw(letter, states);
    if(!skin) return;
    target.draw(colorText, states);
    target.draw(leaveText, states);
    if(state == MenuState::NAME) {
        target.draw(arrowUp, states);
        target.draw(arrowDown, states);
    } else if(state == MenuState::COLOR) {
        target.draw(colorArrow, states);
    } else if(state == MenuState::LEAVE) {
        target.draw(leaveArrow, states);
    }
}

void PlayerMenu::setSkin(PlayerSkin *skin) {
    PlayerMenu::skin = skin;
    update();
}

void PlayerMenu::update() {
    sf::Color main = skin ? skin->getColor() : noColor;
    outline.setOutlineColor(main);
    std::string text(skin ? skin->name : "?  ");
    for (unsigned int i = 0; i < 3; ++i) {
        name[i].setString(text[i]);
        name[i].setFillColor(skin ? sf::Color::White : noColor);
        name[i].setOrigin(std::min((int)(name[i].getGlobalBounds().width+1)/2u, 7u), 0);  // Center glyphs
    }

    if(!skin) return;

    arrowUp.setPosition(20*letterIndex+10, 4);
    arrowDown.setPosition(20*letterIndex+10, 24);
    arrowUp.setColor(main);
    arrowDown.setColor(main);

    colorText.setFillColor(state==MenuState::COLOR?main:noColor);
    colorArrow.setColor(skin->getColor(1));

    leaveText.setFillColor(state==MenuState::LEAVE?leaveColor:noColor);
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
                case Control::A:
                    if(letterIndex<2) letterIndex++;
                    else state = MenuState::COLOR;
                    break;
                default: break;
            }
            break;
        case MenuState::COLOR:
            switch (control) {
                case Control::Up:
                    state = MenuState::NAME;
                    break;
                case Control::Down:
                    state = MenuState::LEAVE;
                    break;
                case Control::Left:
                    skin->setColor(-1);
                    break;
                case Control::Right:
                case Control::A:
                    skin->setColor(+1);
                    break;
                default:
                    break;
            }
            break;
        case MenuState::LEAVE:
            if (control == Control::Up)
                state = MenuState::COLOR;
            break;
    }
    update();
}
