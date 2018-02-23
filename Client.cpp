//
// Created by zeroji on 2/23/18.
//

#include "Client.hpp"

Client::Client() : window(sf::VideoMode(416, 288), "BOOM"), renderer(&engine, &window) {}

void Client::run() {
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            processEvent(event);
        }
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
            break;
    }
}

void Client::render() {
    window.clear(sf::Color::Black);
    renderer.render();
    window.display();
}