#pragma once
#include "PvZSprite.h"
#include "Zombie.h"
#include "Arms.h"
// 植物基类
class Plant : public PvZSprite 
{
public:
    Plant(const char* sprite_name, double health, int attack_interval);
    virtual void attack(float delta_time) = 0;
    virtual bool attacked_by(Zombie* zombie);
    
    const char* get_type() override;

protected:
    double health;                      // 血量
    long double next_attack;            // 距离下次攻击时间
    const float attack_interval;        // 攻击间隔
    static const char* type;            // 类型
};

// 豌豆射手 继承自植物基类
class PeaShooter : public Plant {

public:
    PeaShooter(const char* plant_name, Pea* pea);
    void attack(float delta_time) override;
private:
    Pea* pea;
};


// 向日葵 继承自植物基类
class Sunflower : public Plant {

public:
    Sunflower(const char* plant_name);
    void attack(float delta_time) override;
private:
    int light_num;
    int light_v;
};

