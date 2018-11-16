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

const std::vector<std::vector<std::pair<Control, sf::Keyboard::Key>>> InputHandler::defaultKeyBindings = {{
                    {Control::Up, sf::Keyboard::Key::W},
                    {Control::Up, sf::Keyboard::Key::Z},
                    {Control::Left, sf::Keyboard::Key::A},
                    {Control::Left, sf::Keyboard::Key::Q},
                    {Control::Down, sf::Keyboard::Key::S},
                    {Control::Right, sf::Keyboard::Key::D},
                    {Control::A, sf::Keyboard::Key::Space},
                    {Control::B, sf::Keyboard::Key::Tab},
                    {Control::Start, sf::Keyboard::Key::T}
        }, {
                    {Control::Down, sf::Keyboard::Key::Down},
                    {Control::Left, sf::Keyboard::Key::Left},
                    {Control::Up, sf::Keyboard::Key::Up},
                    {Control::Right, sf::Keyboard::Key::Right},
                    {Control::A, sf::Keyboard::Key::RShift},
                    {Control::B, sf::Keyboard::Key::RControl},
                    {Control::Start, sf::Keyboard::Key::Return}
        }, {
                    {Control::Up, sf::Keyboard::Key::Numpad8},
                    {Control::Left, sf::Keyboard::Key::Numpad4},
                    {Control::Down, sf::Keyboard::Key::Numpad2},
                    {Control::Right, sf::Keyboard::Key::Numpad6},
                    {Control::A, sf::Keyboard::Key::Numpad7},
                    {Control::B, sf::Keyboard::Key::Numpad9},
                    {Control::Start, sf::Keyboard::Key::Numpad0}
        }, {
                    {Control::Up, sf::Keyboard::Key::I},
                    {Control::Left, sf::Keyboard::Key::J},
                    {Control::Down, sf::Keyboard::Key::K},
                    {Control::Right, sf::Keyboard::Key::L},
                    {Control::A, sf::Keyboard::Key::U},
                    {Control::B, sf::Keyboard::Key::O},
                    {Control::Start, sf::Keyboard::Key::M}
        }};

InputHandler::InputHandler(Client *client, const unsigned int &uid, const bool &isKeyboard, const unsigned int &deviceId) :
        client(client), uid(uid), isKeyboard(isKeyboard), deviceId(deviceId) {}

KeyboardHandler::KeyboardHandler(Client *client, const unsigned int &uid, const unsigned int &bindingsId) : InputHandler(client, uid, true, bindingsId) {
    for(auto &pair : defaultKeyBindings[bindingsId])
        mapping.emplace_back(std::pair<Control, Input>(pair.first, Input(pair.second)));
}

JoystickHandler::JoystickHandler(Client *client, const unsigned int &uid, const unsigned int &joystickId) : InputHandler(client, uid, false, joystickId) {
    mapping.emplace_back(std::pair<Control, Input>(Control::Up, Input(joystickId, sf::Joystick::Axis::Y, false)));
    mapping.emplace_back(std::pair<Control, Input>(Control::Left, Input(joystickId, sf::Joystick::Axis::X, false)));
    mapping.emplace_back(std::pair<Control, Input>(Control::Down, Input(joystickId, sf::Joystick::Axis::Y, true)));
    mapping.emplace_back(std::pair<Control, Input>(Control::Right, Input(joystickId, sf::Joystick::Axis::X, true)));
    mapping.emplace_back(std::pair<Control, Input>(Control::Up, Input(joystickId, sf::Joystick::Axis::PovY, false)));
    mapping.emplace_back(std::pair<Control, Input>(Control::Left, Input(joystickId, sf::Joystick::Axis::PovX, false)));
    mapping.emplace_back(std::pair<Control, Input>(Control::Down, Input(joystickId, sf::Joystick::Axis::PovY, true)));
    mapping.emplace_back(std::pair<Control, Input>(Control::Right, Input(joystickId, sf::Joystick::Axis::PovX, true)));
    mapping.emplace_back(std::pair<Control, Input>(Control::A, Input(joystickId, 0u)));
    mapping.emplace_back(std::pair<Control, Input>(Control::B, Input(joystickId, 1u)));
    mapping.emplace_back(std::pair<Control, Input>(Control::Start, Input(joystickId, 7u)));
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

InputHandlerArray::InputHandlerArray(Client *client) : client(client) {}

void InputHandlerArray::setAutoAdd(bool autoAdd) {
    InputHandlerArray::autoAdd = autoAdd;
}

bool InputHandlerArray::dispatch(const sf::Event &event) {
    bool processed = false;
    for (auto &handler : *this) {
        if(handler && handler->dispatch(event))
            processed = true;
    }
    if(!processed && autoAdd) {
        switch (event.type) {
            case sf::Event::JoystickConnected:
                processed = newJoystick(event.joystickConnect.joystickId);
                break;
            case sf::Event::JoystickButtonPressed:
                processed = newJoystick(event.joystickButton.joystickId);
                break;
            case sf::Event::KeyPressed:
                processed = newKeyboard(event.key.code);
                break;
            default:
                break;
        }
    }
    return processed;
}

bool InputHandlerArray::newJoystick(const unsigned int &joystickId) {
    for (auto &handler : *this)
        if(handler && !handler->isKeyboard && handler->deviceId == joystickId)
            return false;
    return addHandler((std::unique_ptr<InputHandler>) new JoystickHandler(client, getNewId(), joystickId));
}

bool InputHandlerArray::newKeyboard(const sf::Keyboard::Key &code) {
    for (unsigned int i = 0; i < InputHandler::defaultKeyBindings.size(); ++i) {
        for (auto &handler : *this)
            if(handler && handler->isKeyboard && handler->deviceId == i)
                continue;
        for (auto &pair : InputHandler::defaultKeyBindings[i]) {
            if(pair.second == code)
                return addHandler((std::unique_ptr<InputHandler>) new KeyboardHandler(client, getNewId(), i));
        }
    }
    return false;
}

unsigned int InputHandlerArray::getNewId() const {
    for (unsigned int i = 0; i < size(); ++i) {
        if (operator[](i) == nullptr)
            return i;
    }
    return (unsigned int) size();
}

bool InputHandlerArray::addHandler(std::unique_ptr<InputHandler> handler) {
    unsigned int index = handler->uid;
    if(index >= size())
        emplace_back(std::move(handler));
    else
        operator[](index) = std::move(handler);
    client->addInput(index);
    return true;
}

void InputHandlerArray::removeHandler(const unsigned int &index) {
    if(index >= size()) return;
    operator[](index) = nullptr;
    while(back() == nullptr)
        pop_back();
}

unsigned int InputHandlerArray::getCount() {
    unsigned int count = 0;
    for(auto &handler : *this)
        if(handler)
            ++count;
    return count;
}
