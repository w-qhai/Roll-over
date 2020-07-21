#include "Plant.h"

const char* Plant::type = "Plant";

Plant::Plant(const char* sprite_name, int health, int attack_interval) :
    PvZSprite(sprite_name),
    health(health), 
    next_attack(0),
    attack_interval(attack_interval) {

}

const char* Plant::get_type() {
    return type;
}

/* --------------------------------------------------- */
PeaShooter::PeaShooter(const char* plant_name, Pea* pea) :
    Plant(plant_name, 200, 150),
    pea(pea)
{
    
}

/// <summary>
/// 时间间隔积累到到一定程度后，进攻
/// </summary>
/// <param name="delta_time">每次时间间隔</param>
void PeaShooter::attack(float delta_time) {
    if ((next_attack -= delta_time) <= 0) {
        pea->SetSpriteLinearVelocityX(20);
        next_attack = attack_interval;
    }
}

