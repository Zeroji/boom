//
// Created by zeroji on 2/27/18.
//

#ifndef BOOM_CONTROL_HPP
#define BOOM_CONTROL_HPP

#include "Direction.hpp"

/**
 * Lists all the different controls in the game
 */
enum class Control : int8_t {
    Up, Down, Left, Right,
    A, B, Start
};

namespace control {
    /**
     * Turns a control into a direction
     * @param control The control to convert
     * @return The corresponding direction or NONE
     */
    Direction toDir(const Control &control);

    /**
     * Tells whether this control is a directional control
     * @param control The control to check
     * @return true if the control is directional
     */
    bool isDir(const Control &control);
}

std::ostream &operator<<(std::ostream &stream, const Control &control);

#endif //BOOM_CONTROL_HPP
