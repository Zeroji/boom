//
// Created by zeroji on 2/23/18.
//

#include <iostream>
#include "Client.hpp"

const sf::Vector2u Client::resolution(320, 180);

Client::Client() : window(sf::VideoMode(resolution.x * 2, resolution.y * 2), "BOOM"),
                   renderer(&engine, &target), engine(15, 11, 5), handlers(this) {
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    renderer.resize(resolution.x, resolution.y);
    target.create(resolution.x, resolution.y);
    target.display();
    targetSprite.setTexture(target.getTexture());

    font.loadFromFile("res/Comic_Sans_MS.ttf");
    playerCount.setFont(font);
    playerCount.setCharacterSize(80);
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
            resize(event.size.width, event.size.height);
            break;
        default:
            handlers.dispatch(event);
            break;
    }
}

void Client::render() {
    window.clear(sf::Color::Black);
    target.clear(sf::Color::Black);
    switch (state) {
        case State::TITLE:
            playerCount.setString(std::to_string(handlers.getCount()));
            target.draw(playerCount);
            break;
        case State::GAME:
            renderer.render();
            break;
    }
    window.draw(targetSprite);
    window.display();
}

void Client::resize(unsigned int width, unsigned int height) {
    window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
    const sf::Vector2u &size = target.getSize();

    // Calculate pixel upscale
    unsigned int scale = 2;
    while(scale * size.x <= width && scale * size.y <= height) ++scale;
    --scale;
    targetSprite.setScale(scale, scale);

    // Calculate render target centering
    sf::Vector2i borders(sf::Vector2f(width, height) - sf::Vector2f(size * scale));
    targetSprite.setPosition(borders.x / 2, borders.y / 2);
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
    engine = Engine(15, 11, handlers.getCount());
    this->state = State::GAME;
}
