//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_CLIENT_HPP
#define BOOM_CLIENT_HPP

#include <SFML/Graphics.hpp>
#include "core/Engine.hpp"
#include "InputHandler.hpp"
#include "PlayerMenu.hpp"
#include "PlayerSkin.hpp"
#include "Renderer.hpp"
#include "ResourceLoader.hpp"

enum class Control : int8_t;

enum class State : int8_t {
    TITLE, GAME
};

/**
 * Handles the entire application, including starting games,
 * managing the window, or calling the engine / renderer
 */
class Client {
public:
    Client();
    static const sf::Vector2u resolution;

    void run();
    void processEvent(sf::Event &event);
    void processInput(const unsigned int &player, const Control &control, bool state, const std::vector<Control> &controls);
    void addInput(const unsigned int &player);
    void removeInput(const unsigned int &player);
    void render();
    void resize(unsigned int width, unsigned int height);

private:
    void startGame();
    void positionMenus();

    State state = State::TITLE;
    InputHandlerArray handlers;
    std::map<unsigned int, unsigned int> inputMapper;
    std::unique_ptr<Engine> engine;
    std::unique_ptr<Renderer> renderer;
    sf::RenderWindow window;
    sf::RenderTexture target;
    sf::Sprite targetSprite;

    ResourceLoader res;

    // Render related
    std::vector<PlayerMenu> menus;
    std::vector<PlayerSkin*> skins;
};


#endif //BOOM_CLIENT_HPP
