//
// Created by zeroji on 2/26/18.
//

#ifndef BOOM_INPUTHANDLER_HPP
#define BOOM_INPUTHANDLER_HPP


#include <map>
#include <SFML/Window/Event.hpp>

#include "Control.hpp"

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
     * Construct from a keyboard input layout
     * Additional handlers will have pre-mapped keybinds, possibly limited
     */
    explicit InputHandler(Client*);

    /**
     * Construct from a joystick input layout
     * Note than SFML only handles 8 joystick
     * @param joystickId The ID of the joystick to use
     */
    explicit InputHandler(Client*, const unsigned int &joystickId);

    /**
     * Process an SFML event and dispatch to client if necessary
     * @param event The event to process
     * @return true if anything was dispatched
     */
    bool dispatch(const sf::Event &event);

private:
    std::vector<Control> controls;
    static unsigned int newUid;
    static unsigned int keyUid;
    static const std::vector<std::vector<std::pair<Control, sf::Keyboard::Key>>> defaultKeyBindings;
    const unsigned int uid;
    Client *client;

    std::vector<std::pair<Control, Input>> mapping;
};

#endif //BOOM_INPUTHANDLER_HPP
