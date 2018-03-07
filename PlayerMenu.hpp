//
// Created by zeroji on 3/6/18.
//

#ifndef BOOM_PLAYERMENU_HPP
#define BOOM_PLAYERMENU_HPP


#include <SFML/Graphics.hpp>
#include "PlayerSkin.hpp"
#include "ResourceLoader.hpp"
#include "Control.hpp"

enum class MenuState { NAME };

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
};


#endif //BOOM_PLAYERMENU_HPP
