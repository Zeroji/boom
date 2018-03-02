//
// Created by zeroji on 2/26/18.
//

#include <cmath>
#include <iostream>
#include "InputHandler.hpp"
#include "Client.hpp"

Input::Input(const sf::Event &event) {
    switch(event.type) {
        case sf::Event::KeyPressed:
            type = InputKey;
            keyCode = event.key.code;
            break;
        case sf::Event::JoystickMoved:
            type = InputAxis;
            joystickID = event.joystickMove.joystickId;
            axisID = event.joystickMove.axis;
            axisPos = event.joystickMove.position > 0;
            break;
        case sf::Event::JoystickButtonPressed:
            type = InputButton;
            joystickID = event.joystickButton.joystickId;
            buttonID = event.joystickButton.button;
            break;
        default:
            break;
    }
}

Input::Input(const sf::Keyboard::Key &code) : type(InputKey), keyCode(code) {}

Input::Input(const unsigned int &joystick, const sf::Joystick::Axis &axis, const bool &positive) : type(InputAxis), joystickID(joystick), axisID(axis), axisPos(positive) {}

Input::Input(const unsigned int &joystick, const unsigned int &button) : type(InputButton), joystickID(joystick), buttonID(button) {}

bool Input::process(const sf::Event &event) {
    bool old = state;
    switch(type) {
        case InputAxis:
            if(event.type != sf::Event::JoystickMoved) return false;
            if(event.joystickMove.joystickId == joystickID && event.joystickMove.axis == axisID) {
                state = std::abs(event.joystickMove.position) >= axisThreshold && ((event.joystickMove.position > 0) == axisPos);
                break;
            }
            return false;
        case InputButton:
            if(event.type != sf::Event::JoystickButtonPressed && event.type != sf::Event::JoystickButtonReleased) return false;
            if(event.joystickButton.joystickId == joystickID && event.joystickButton.button == buttonID)
                state = event.type == sf::Event::JoystickButtonPressed;
            break;
        case InputKey:
            if(event.type != sf::Event::KeyPressed && event.type != sf::Event::KeyReleased) return false;
            if(event.key.code == keyCode)
                state = event.type == sf::Event::KeyPressed;
            break;
    }
    changed = old != state;
    return changed;
}

bool Input::getState() const {
    return state;
}

bool Input::hasChanged() const {
    return changed;
}

Input &Input::operator=(Input input) {
    type = input.type; keyCode = input.keyCode;
    joystickID = input.joystickID; axisID = input.axisID; axisPos = input.axisPos;
    buttonID = input.buttonID; state = input.state; changed = input.changed;
    return *this;
}

unsigned int InputHandler::newUid = 0;
unsigned int InputHandler::keyUid = 0;

const std::vector<std::vector<std::pair<Control, sf::Keyboard::Key>>> InputHandler::defaultKeyBindings = {{
                    {Control::Down, sf::Keyboard::Key::S},
                    {Control::Up, sf::Keyboard::Key::W},
                    {Control::Up, sf::Keyboard::Key::Z},
                    {Control::Left, sf::Keyboard::Key::Q},
                    {Control::Left, sf::Keyboard::Key::A},
                    {Control::Right, sf::Keyboard::Key::D},
                    {Control::A, sf::Keyboard::Key::Space},
                    {Control::B, sf::Keyboard::Key::Tab}
        }, {
                    {Control::Down, sf::Keyboard::Key::Down},
                    {Control::Up, sf::Keyboard::Key::Up},
                    {Control::Left, sf::Keyboard::Key::Left},
                    {Control::Right, sf::Keyboard::Key::Right},
                    {Control::A, sf::Keyboard::Key::RShift},
                    {Control::B, sf::Keyboard::Key::RControl}
        }, {
                    {Control::Down, sf::Keyboard::Key::Numpad2},
                    {Control::Up, sf::Keyboard::Key::Numpad8},
                    {Control::Left, sf::Keyboard::Key::Numpad4},
                    {Control::Right, sf::Keyboard::Key::Numpad6},
                    {Control::A, sf::Keyboard::Key::Numpad7},
                    {Control::B, sf::Keyboard::Key::Numpad9}
        }};

InputHandler::InputHandler(Client *client) : client(client), uid(newUid++) {
    for(auto &pair : defaultKeyBindings[keyUid++])
        mapping.emplace_back(std::pair<Control, Input>(pair.first, Input(pair.second)));
}

InputHandler::InputHandler(Client *client, const unsigned int &joystickId) : client(client), uid(newUid++) {
    mapping.emplace_back(std::pair<Control, Input>(Control::Down, Input(joystickId, sf::Joystick::Axis::Y, true)));
    mapping.emplace_back(std::pair<Control, Input>(Control::Up, Input(joystickId, sf::Joystick::Axis::Y, false)));
    mapping.emplace_back(std::pair<Control, Input>(Control::Right, Input(joystickId, sf::Joystick::Axis::X, true)));
    mapping.emplace_back(std::pair<Control, Input>(Control::Left, Input(joystickId, sf::Joystick::Axis::X, false)));
    mapping.emplace_back(std::pair<Control, Input>(Control::A, Input(joystickId, 0u)));
    mapping.emplace_back(std::pair<Control, Input>(Control::B, Input(joystickId, 1u)));
}

bool InputHandler::dispatch(const sf::Event &event) {
    bool processed = false;
    for(auto &it: mapping) {
        if(it.second.process(event)) {
            if(it.second.getState()) {
                if(std::find(controls.begin(), controls.end(), it.first) == controls.end()) {
                    controls.emplace(controls.begin(), it.first);
                }
            } else {
                controls.erase(std::remove(controls.begin(), controls.end(), it.first), controls.end());
            }
            client->processInput(uid, it.first, it.second.getState(), controls);
            processed = true;
        }
    }
    return processed;
}
