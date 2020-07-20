#pragma once
#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_

#include "CommonClass.h"

class Zombie : public CAnimateSprite {
public:
    Zombie();
    void move();
    void eat_plants();
    void attacked();
    void die();
private:
    int health;
    int speed;
};

#endif // !_ZOMBIE_H_
