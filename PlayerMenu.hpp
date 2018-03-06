//
// Created by zeroji on 3/6/18.
//

#ifndef BOOM_PLAYERMENU_HPP
#define BOOM_PLAYERMENU_HPP


#include <SFML/Graphics.hpp>
#include "PlayerSkin.hpp"

class PlayerMenu : public sf::Drawable, public sf::Transformable {
public:
    PlayerMenu(sf::Font &font, PlayerSkin *skin);
    void setSkin(PlayerSkin *skin);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Font &font;
    PlayerSkin* skin;

    sf::RectangleShape outline;
    sf::Text name;
};


#endif //BOOM_PLAYERMENU_HPP
