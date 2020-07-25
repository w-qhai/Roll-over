#pragma once
#include "PvZSprite.h"
#include "Arms.h"
#include "SuperSound.h"

class Zombie : public PvZSprite {
public:
    Zombie(const char* sprite_name, int health, int speed, double power);
    const char* get_type() override;

    virtual void move() = 0;
    virtual void stop() = 0;
    virtual void eat_plant() = 0;
    virtual void die() = 0;
    virtual void attacked_by(Arms* arm) = 0;
    virtual double  get_power() = 0;
    virtual void set_status() = 0;
    bool is_eating();
protected:
    int health;
    int move_speed;
    double power;
    bool eating;

    float next_attack;                // 距离下次攻击时间
    const float attack_interval;      // 攻击间隔
    static const char* type;
};

class OrdinaryZombie : public Zombie {
public:
    OrdinaryZombie(const char* zombie_name);
    ~OrdinaryZombie();
    void move() override;
    void stop() override;
    void eat_plant() override;
    void die() override;
    void attacked_by(Arms* arm) override;
    double  get_power() override;
    void set_status() override;
};
