//
// Created by zeroji on 2/27/18.
//

#include <ostream>
#include "Control.hpp"

std::ostream &operator<<(std::ostream &stream, const Control &control) {
    switch (control) {
        case Control::Up: stream << "^"; break;
        case Control::Down: stream << "v"; break;
        case Control::Left: stream << "<"; break;
        case Control::Right: stream << ">"; break;
        case Control::A: stream << "A"; break;
        case Control::B: stream << "B"; break;
    }
    return stream;
}

Direction control::toDir(const Control &control) {
    switch (control) {
        case Control::Up: return UP;
        case Control::Down: return DOWN;
        case Control::Left: return LEFT;
        case Control::Right: return RIGHT;
        default: return NONE;
    }
}

bool control::isDir(const Control &control) {
    return toDir(control) != NONE;
}
