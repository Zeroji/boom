//
// Created by zeroji on 3/6/18.
//

#ifndef BOOM_PLAYERMENU_HPP
#define BOOM_PLAYERMENU_HPP


#include <SFML/Graphics.hpp>
#include "PlayerSkin.hpp"
#include "ResourceLoader.hpp"
#include "Control.hpp"

enum class MenuState { NAME, COLOR, LEAVE };

class PlayerMenu : public sf::Drawable, public sf::Transformable {
public:
    PlayerMenu(const ResourceLoader &res, PlayerSkin *skin);
    void setSkin(PlayerSkin *skin);
    void keyPressed(const Control &control);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update();

    const ResourceLoader &res;
    PlayerSkin* skin;

    MenuState state;
    unsigned int letterIndex;

    sf::RectangleShape outline;
    std::vector<sf::Text> name;
    sf::Sprite arrowUp, arrowDown;

    sf::Text colorText, leaveText;
    sf::Sprite colorArrow, leaveArrow;

    static const sf::Color noColor, leaveColor;
};


#endif //BOOM_PLAYERMENU_HPP
