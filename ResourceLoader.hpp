//
// Created by zeroji on 3/6/18.
//

#ifndef BOOM_RESOURCELOADER_HPP
#define BOOM_RESOURCELOADER_HPP


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class ResourceLoader {
public:
    const sf::Texture tiles;
    const sf::Texture player;
    const sf::Texture arrow;
    const sf::Texture bomb;
    const sf::Texture beams;
    const sf::Font font;

    explicit ResourceLoader(const std::string &path);

protected:
    static sf::Texture loadTexture(const std::string &path, const std::string &filename);
    static sf::Font loadFont(const std::string &path, const std::string &filename);

};


#endif //BOOM_RESOURCELOADER_HPP
