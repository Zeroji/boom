//
// Created by zeroji on 2/23/18.
//

#include <iostream>
#include "Client.hpp"

const sf::Vector2u Client::resolution(320, 180);

Client::Client() : window(sf::VideoMode(resolution.x * 2, resolution.y * 2), "BOOM"), handlers(this), res("res") {
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    target.create(resolution.x, resolution.y);
    target.display();
    targetSprite.setTexture(target.getTexture());
}

void Client::run() {
    sf::Clock clock;
    while(window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            processEvent(event);
        }
        if(state == State::GAME)
            engine->update(clock.restart());
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
            for(auto &menu: menus)
                target.draw(menu);
            break;
        case State::GAME:
            renderer->render();
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
            if(state && player<menus.size()) {
                menus[player].keyPressed(control);
                if(menus[player].hasLeft()) removeInput(player);
                if(control == Control::Start) {
                    unsigned int ready=0, total=0;
                    for(auto &menu: menus) {
                        if(menu.hasSkin()) ++total;
                        if(menu.isReady()) ++ready;
                    }
                    if(total >= 2 && ready == total)
                        startGame();
                }
            }
            break;
        case State::GAME:
            engine->processInput(inputMapper[player], control, state, controls);
            break;
    }
}

void Client::addInput(const unsigned int &player) {
    while (player >= skins.size()) skins.emplace_back(nullptr);
    skins[player] = new PlayerSkin(player);
    while (player >= menus.size()) menus.emplace_back(PlayerMenu(res, nullptr));
    menus[player].setSkin(skins[player]);
    positionMenus();
}

void Client::removeInput(const unsigned int &player) {
    handlers.removeHandler(player);
    menus[player].setSkin(nullptr);
    delete skins[player];
    skins[player] = nullptr;
    while(skins.back() == nullptr) { skins.pop_back(); menus.pop_back(); }
    positionMenus();
}

void Client::startGame() {
    handlers.setAutoAdd(false);
    inputMapper.clear();
    unsigned int index = 0;
    for(const auto &handler : handlers)
        if(handler)
            inputMapper[handler->uid] = index++;
    std::vector<PlayerSkin*> renderSkins;
    for(auto &skin: skins)
        if(skin)
            renderSkins.emplace_back(skin);
    engine.reset(new Engine(15, 11, handlers.getCount()));
    renderer.reset(new Renderer(res, engine.get(), &target, renderSkins));
    this->state = State::GAME;
}

void Client::positionMenus() {
    // less than 4: side by side, row centered horizontally
    // more than 3: two rows of roughly equal lengths
    const unsigned long &size = menus.size();
    unsigned long pivot = (size+1) / 2;
    if(size <= 3) pivot = size;
    sf::Vector2f pos(0, 0);
    for (int i = 0; i < menus.size(); ++i) {
        if(i<pivot)
            pos.x = i - pivot / 2.f;
        else
            pos.x = (i - pivot)  - (size - pivot) / 2.f;
        if(size < 4)
            pos.y = 1 / 2.f;
        else
            pos.y = i < pivot ? 0 : 1;
        pos.x += 2;                 // center
        pos.x *= 80; pos.y *= 60;   // scale
        pos.y += 60;                // offset
        menus[i].setPosition(pos);
    }
}
