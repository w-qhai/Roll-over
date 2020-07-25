#pragma once
#include "PvZSprite.h"
#include "Zombie.h"
#include "Arms.h"
// 植物基类
class Plant : public PvZSprite
{
public:
	Plant(const char* sprite_name, double health, int attack_interval);
	Plant(const char* sprite_name, double health);

	virtual void attack(float delta_time) = 0;
	virtual bool attacked_by(Zombie* zombie);

	const char* get_type() override;

protected:
	int line;                           // 在哪行
	double health;                      // 血量
	float next_attack;                  // 距离下次攻击时间
	float attack_interval;        // 攻击间隔
	static const char* type;            // 类型
};

/* --------------------------------------------------- */
// 豌豆射手 继承自植物基类
class PeaShooter : public Plant {

public:
	PeaShooter(const char* plant_name, Pea* pea);
	void attack(float delta_time) override;

private:
	Pea* pea;
};


/* --------------------------------------------------- */
// 向日葵 继承自植物基类
class SunFlower : public Plant {
public:
	SunFlower(const char* plant_name);
	void attack(float delta_time) override;

protected:
	double light_num;                   // 产生光量
	double light_v;						// 产生一次光的时间
};
/* --------------------------------------------------- */