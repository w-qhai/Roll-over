#pragma once
#include "PvZSprite.h"
class Plant : public PvZSprite {

public:
    Plant(const char* sprite_name, int health, int attack_interval);
    virtual void attack(float delta_time) = 0;
    const char* get_type() override;
protected:
    int health;
    int next_attack;
    const int attack_interval;
    static const char* type;
};

