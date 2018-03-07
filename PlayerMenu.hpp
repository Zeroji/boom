//
// Created by zeroji on 3/6/18.
//

#ifndef BOOM_PLAYERMENU_HPP
#define BOOM_PLAYERMENU_HPP


#include <SFML/Graphics.hpp>
#include "PlayerSkin.hpp"
#include "ResourceLoader.hpp"
#include "Control.hpp"

enum class MenuState { NAME, COLOR, LEAVE, READY };

class PlayerMenu : public sf::Drawable, public sf::Transformable {
public:
    PlayerMenu(const ResourceLoader &res, PlayerSkin *skin);
    void setSkin(PlayerSkin *skin);
    void keyPressed(const Control &control);
    inline bool hasSkin() const { return skin != nullptr; }
    inline bool isReady() const { return state == MenuState::READY; }
    inline bool hasLeft() const { return left; }

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update();

    const ResourceLoader &res;
    PlayerSkin* skin;

    MenuState state;
    unsigned int letterIndex;
    bool left;

    sf::RectangleShape outline;
    sf::Sprite playerSpr;
    Direction playerDir=RIGHT;
    std::vector<sf::Text> name;
    sf::Sprite arrowUp, arrowDown;

    sf::Text colorText, leaveText, readyText;
    sf::Sprite colorArrow, leaveArrow;

    static const sf::Color noColor, leaveColor;
};


#endif //BOOM_PLAYERMENU_HPP
