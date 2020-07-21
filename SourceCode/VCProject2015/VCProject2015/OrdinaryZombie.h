#pragma once
#include "Zombie.h"
class OrdinaryZombie : public Zombie {
public:
    OrdinaryZombie(const char* zombie_name);
    void move() override;
    void eat_plant() override;
    void die() override;
};

