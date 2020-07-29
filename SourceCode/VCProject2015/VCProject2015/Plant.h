#pragma once
#include "PvZSprite.h"
#include "Zombie.h"
#include "Arms.h"
// 植物基类
class Plant : public PvZSprite 
{
public:
    Plant(const char* sprite_name, double health, int attack_interval, int cost);
    virtual int attack(float delta_time) = 0;
    virtual bool attacked_by(Zombie* zombie);
    
    const char* get_type() override;
    void set_exist(bool exist);
    int get_cost() { return cost; }
protected:
    double health;                      // 血量
    long double next_attack;            // 距离下次攻击时间
    const float attack_interval;        // 攻击间隔
    static const char* type;            // 类型
    int cost;                           // 消耗阳光
};

// 豌豆射手 继承自植物基类
class PeaShooter : public Plant {

public:
    PeaShooter(const char* plant_name, Pea* pea);
    int attack(float delta_time) override;
private:
    Pea* pea;
};


// 向日葵 继承自植物基类
class Sunflower : public Plant {

public:
    Sunflower(const char* plant_name);
    int attack(float delta_time) override;
private:
    int light_num;
    int light_v;
};

// 樱桃炸弹 继承自植物基类
class CherryBomb : public Plant {

public:
    CherryBomb(const char* plant_name, Boom* boom);
    int attack(float delta_time) override;
private:
    Boom* boom;
};


