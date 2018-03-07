//
// Created by zeroji on 3/6/18.
//

#ifndef BOOM_PLAYERSKIN_HPP
#define BOOM_PLAYERSKIN_HPP

#include <SFML/Graphics/Color.hpp>
#include <vector>

class PlayerSkin {
public:
    explicit PlayerSkin(unsigned int id);

    char name[4] = "AAA";
    unsigned int color = 0;
    const sf::Color &getColor() const;
    const sf::Color &getColor(int delta) const;
    void setColor(int delta);

private:
    const static std::vector<sf::Color> colors;
};


#endif //BOOM_PLAYERSKIN_HPP
