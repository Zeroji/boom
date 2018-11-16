//
// Created by zeroji on 2/26/18.
//

#ifndef BOOM_INPUTHANDLER_HPP
#define BOOM_INPUTHANDLER_HPP


#include <map>
#include <vector>
#include <SFML/Window/Event.hpp>
#include "core/Control.hpp"

class Client;

enum InputType { InputAxis, InputButton, InputKey };

/**
 * Describe one single input method, bound to a control
 *
 * This can be either a joystick axis move, button press, or a key press
 */
class Input {
public:
    Input() = default;
    Input(const Input &input) = default;
    Input &operator=(Input);

    /**
     * Construct from an SFML window Event
     * Useful for in-game binding
     * @param event The event to gather data from
     */
    explicit Input(const sf::Event &event);

    /**
     * Construct a keyboard input from a key code
     * @param code The SFML key code
     */
    explicit Input(const sf::Keyboard::Key &code);

    /**
     * Construct a joystick axis input from data
     * @param joystick The ID of the joystick to use
     * @param axis The ID of the axis to use
     * @param positive true if this should be triggered when the axis is moved positively
     */
    Input(const unsigned int &joystick, const sf::Joystick::Axis &axis, const bool &positive);

    /**
     * Construct a joystick button input from data
     * @param joystick The ID of the joystick to use
     * @param button The ID of the button to use
     */
    Input(const unsigned int &joystick, const unsigned int &button);

    /**
     * Process an event, and update self if necessary
     * @param event The event to process
     * @return true if the state changed
     */
    bool process(const sf::Event &event);

    /**
     * Gets the current state (active/inactive) of the input
     * @return Input state
     */
    bool getState() const;

    /**
     * Check if the input state has changed during the last event processing
     * @return true if the input state has changed
     */
    bool hasChanged() const;

private:
    InputType type;
    sf::Keyboard::Key keyCode;
    unsigned int joystickID;
    sf::Joystick::Axis axisID;
    bool axisPos;
    const float axisThreshold = 25;  // This value is an arbitrary percentage for dead zones
    unsigned int buttonID;

    bool state = false;
    bool changed = false;
};

/**
 * Processes events into controls
 *
 * Dispatches control-based events to the associated client
 */
class InputHandler {
public:
    /**
     * Process an SFML event and dispatch to client if necessary
     * @param event The event to process
     * @return true if anything was dispatched
     */
    bool dispatch(const sf::Event &event);

    const bool isKeyboard;
    const unsigned int deviceId;
    const unsigned int uid;

    static const std::vector<std::vector<std::pair<Control, sf::Keyboard::Key>>> defaultKeyBindings;
protected:
    InputHandler(Client *client, const unsigned int &uid, const bool &isKeyboard, const unsigned int &deviceId);
    std::vector<Control> controls;
    Client *client;

    std::vector<std::pair<Control, Input>> mapping;
};

/**
 * Construct from a keyboard input layout
 * Additional handlers will have pre-mapped keybinds, possibly limited
 */
class KeyboardHandler : public InputHandler {
public:
    KeyboardHandler(Client *client, const unsigned int &uid, const unsigned int &bindingsId);
};

/**
 * Construct from a joystick input layout
 * Note than SFML only handles 8 joystick
 */
class JoystickHandler : public InputHandler {
public:
    JoystickHandler(Client *client, const unsigned int &uid, const unsigned int &joystickId);
};

class InputHandlerArray : public std::vector<std::unique_ptr<InputHandler>> {
public:
    explicit InputHandlerArray(Client *client);

    /**
     * Process an SFML event and dispatch to client if necessary
     * @param event The event to process
     * @return true if anything was dispatched
     */
    bool dispatch(const sf::Event &event);

    void setAutoAdd(bool autoAdd);
    void removeHandler(const unsigned int &index);
    unsigned int getCount();

private:
    Client *client;
    bool autoAdd = true;

    bool newJoystick(const unsigned int &joystickId);
    bool newKeyboard(const sf::Keyboard::Key &code);
    unsigned int getNewId() const;
    bool addHandler(std::unique_ptr<InputHandler> handler);
};

#endif //BOOM_INPUTHANDLER_HPP
