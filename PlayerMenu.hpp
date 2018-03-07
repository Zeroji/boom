//
// Created by zeroji on 3/6/18.
//

#ifndef BOOM_PLAYERMENU_HPP
#define BOOM_PLAYERMENU_HPP


#include <SFML/Graphics.hpp>
#include "PlayerSkin.hpp"
#include "ResourceLoader.hpp"

class PlayerMenu : public sf::Drawable, public sf::Transformable {
public:
    PlayerMenu(const ResourceLoader &res, PlayerSkin *skin);
    void setSkin(PlayerSkin *skin);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    const ResourceLoader &res;
    PlayerSkin* skin;

    sf::RectangleShape outline;
    std::vector<sf::Text> name;
};


#endif //BOOM_PLAYERMENU_HPP
