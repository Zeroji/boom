//
// Created by zeroji on 2/23/18.
//

#ifndef BOOM_ENGINE_HPP
#define BOOM_ENGINE_HPP


#include "Map.hpp"

class Engine {
public:
    Engine();

private:
    Map map;
public:
    const Map &getMap() const;
};


#endif //BOOM_ENGINE_HPP
