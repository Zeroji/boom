//
// Created by zeroji on 2/23/18.
//

#include <iostream>
#include "Client.hpp"

Client::Client() : window(sf::VideoMode(800, 544), "BOOM"), renderer(&engine, &window), engine(25, 17, 5), handlers(this) {
    window.setKeyRepeatEnabled(false);
}

void Client::run() {
    sf::Clock clock;
    while(window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            processEvent(event);
        }
        engine.update(clock.restart());
        render();
    }
}

void Client::processEvent(sf::Event &event) {
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::Resized:
            renderer.resize(event.size.width, event.size.height);
            break;
        default:
            handlers.dispatch(event);
            break;
    }
}

void Client::render() {
    window.clear(sf::Color::Black);
    renderer.render();
    window.display();
}

void Client::processInput(const unsigned int &player, const Control &control, bool state, const std::vector<Control> &controls) {
    engine.processInput(player, control, state, controls);
}

void Client::addInput(const unsigned int &player) {

}
