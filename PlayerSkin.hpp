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

    char name[4] = "ABC";
    sf::Color color = sf::Color::Red;

private:
    const static std::vector<sf::Color> defaultColors;
};


#endif //BOOM_PLAYERSKIN_HPP
