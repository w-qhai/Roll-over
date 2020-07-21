#pragma once
#include "PvZSprite.h"


class Zombie : public PvZSprite {
public:
    Zombie(const char* sprite_name, int health, int speed);

    virtual void move() = 0;
    virtual void eat_plant() = 0;
    virtual void die();

    const char* get_type() override;
protected:
    int health;
    int move_speed;
    static const char* type;
};

class OrdinaryZombie : public Zombie {
public:
    OrdinaryZombie(const char* zombie_name);
    void move() override;
    void eat_plant() override;
    void die() override;
};
