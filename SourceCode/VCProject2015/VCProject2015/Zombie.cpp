#include "Zombie.h"

const char* Zombie::type = "Zombie";

Zombie::Zombie(const char* sprite_name, int health, int move_speed) :
    PvZSprite(sprite_name),
    health(health),
    move_speed(move_speed)
{

}

void Zombie::die() {

}

const char* Zombie::get_type() {
    return type;
}

/////////////////////////

OrdinaryZombie::OrdinaryZombie(const char* zombie_name) :
    Zombie(zombie_name, 200, 3)
{

}

/// <summary>
/// ÈÃ½©Ê¬¿ªÊ¼ÒÆ¶¯
/// </summary>
void OrdinaryZombie::move() {
    this->SetSpriteLinearVelocityX(-this->move_speed);
}

void OrdinaryZombie::eat_plant() {

}

void OrdinaryZombie::die() {
    this->AnimateSpritePlayAnimation("ZombieDieAnimation", false);
    this->SetSpriteWidth(20.625);
    this->SetSpriteHeight(10.625);
    this->SetSpriteLinearVelocityX(-6);
    this->SetSpriteLifeTime(1);
}
