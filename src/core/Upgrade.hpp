//
// Created by zeroji on 4/12/18.
//

#ifndef BOOM_UPGRADE_HPP
#define BOOM_UPGRADE_HPP

#include <cstdint>

enum class UpType : uint8_t {
    BOMB_COUNT, BOMB_RANGE, SPEED, SHIELD
};

class Upgrade {
public:
    explicit Upgrade(const UpType &type);
    UpType type;
};


#endif //BOOM_UPGRADE_HPP
