#pragma once
#include "PvZSprite.h"
#include "Arms.h"
// 植物基类
class Plant : public PvZSprite 
{
public:
    Plant(const char* sprite_name, int health, int attack_interval);
    virtual void attack(float delta_time) = 0;
    const char* get_type() override;
protected:
    int health;                     // 血量
    int next_attack;                // 距离下次攻击时间
    const int attack_interval;      // 攻击间隔
    static const char* type;        // 类型
};

// 豌豆射手 继承自植物基类
class PeaShooter : public Plant {

public:
    PeaShooter(const char* plant_name, Pea* pea);
    void attack(float delta_time) override;
private:
    Pea* pea;
};

