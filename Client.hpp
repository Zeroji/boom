//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_CLIENT_HPP
#define BOOM_CLIENT_HPP

#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"

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
    void render();
    void resize(unsigned int width, unsigned int height);

private:
    void startGame();

    State state = State::TITLE;
    InputHandlerArray handlers;
    std::map<unsigned int, unsigned int> inputMapper;
    Engine engine;
    Renderer renderer;
    sf::RenderWindow window;
    sf::RenderTexture target;
    sf::Sprite targetSprite;

    // Render related
    sf::Font font;
    sf::Text playerCount;
};


#endif //BOOM_CLIENT_HPP
