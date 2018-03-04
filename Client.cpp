//
// Created by zeroji on 2/23/18.
//

#include <iostream>
#include "Client.hpp"

Client::Client() : window(sf::VideoMode(800, 544), "BOOM"), renderer(&engine, &window), engine(25, 17, 5), handlers(this) {
    window.setKeyRepeatEnabled(false);

    font.loadFromFile("res/Comic_Sans_MS.ttf");
    playerCount.setFont(font);
    playerCount.setCharacterSize(200);
    playerCount.setFillColor(sf::Color::White);
    playerCount.setString("0");
    playerCount.setPosition(40, 40);
}

void Client::run() {
    sf::Clock clock;
    while(window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            processEvent(event);
        }
        if(state == State::GAME)
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
    switch (state) {
        case State::TITLE:
            playerCount.setString(std::to_string(handlers.getCount()));
            window.draw(playerCount);
            break;
        case State::GAME:
            renderer.render();
            break;
    }
    window.display();
}

void Client::processInput(const unsigned int &player, const Control &control, bool state, const std::vector<Control> &controls) {
    switch (this->state) {
        case State::TITLE:
            if(control == Control::Start)
                startGame();
            if(control == Control::B) {
                handlers.removeHandler(player);
            }
            break;
        case State::GAME:
            engine.processInput(inputMapper[player], control, state, controls);
            break;
    }
}

void Client::addInput(const unsigned int &player) {

}

void Client::startGame() {
    handlers.setAutoAdd(false);
    inputMapper.clear();
    unsigned int index = 0;
    for(const auto &handler : handlers)
        if(handler)
            inputMapper[handler->uid] = index++;
    engine = Engine(25, 17, handlers.getCount());
    this->state = State::GAME;
}
