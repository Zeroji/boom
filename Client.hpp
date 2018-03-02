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

/**
 * Handles the entire application, including starting games,
 * managing the window, or calling the engine / renderer
 */
class Client {
public:
    Client();

    void run();
    void processEvent(sf::Event &event);
    void processInput(const unsigned int &player, const Control &control, bool state, const std::vector<Control> &controls);
    void render();

private:
    std::vector<std::unique_ptr<InputHandler>> handlers;
    Engine engine;
    Renderer renderer;
    sf::RenderWindow window;
};


#endif //BOOM_CLIENT_HPP
