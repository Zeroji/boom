//
// Created by zeroji on 2/23/18.
//

#include "Engine.hpp"

Engine::Engine(): map(13, 9) {}

const Map &Engine::getMap() const {
    return map;
}
