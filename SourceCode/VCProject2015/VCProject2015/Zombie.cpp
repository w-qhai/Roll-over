#include "Zombie.h"

const char* Zombie::type = "Zombie";

Zombie::Zombie(const char* sprite_name, int health, int move_speed, int power) :
    PvZSprite(sprite_name),
    health(health),
    move_speed(move_speed),
    power(power),
    next_attack(0),
    attack_interval(500),
{

}

const char* Zombie::get_type() {
    return type;
}


/////////////////////////

OrdinaryZombie::OrdinaryZombie(const char* zombie_name) :
    Zombie(zombie_name, 200, 3, 50)
{

}

/// <summary>
/// 让僵尸开始移动
/// </summary>
void OrdinaryZombie::move() {
    this->SetSpriteLinearVelocityX(-this->move_speed);
    if (this->health < 100) {
        this->AnimateSpritePlayAnimation("ZombieLoseHeadAnimation", false);
        this->SetSpriteWidth(10.000);
        this->SetSpriteHeight(11.875);
    }
    else {
        this->AnimateSpritePlayAnimation("OrdinaryZombieAnimation", false);
        this->SetSpriteWidth(10.875);
        this->SetSpriteHeight(15.500);
    }
}

void OrdinaryZombie::stop() {
    this->SetSpriteLinearVelocityX(0);
    if (this->health < 100) {
        this->AnimateSpritePlayAnimation("ZombieLoseHeadAnimation", false);
        this->SetSpriteWidth(10.000);
        this->SetSpriteHeight(11.875);
    }
    else {
        this->AnimateSpritePlayAnimation("OrdinaryZombieAnimation", false);
        this->SetSpriteWidth(10.875);
        this->SetSpriteHeight(15.500);
    }
}

void OrdinaryZombie::eat_plant() {
    this->SetSpriteLinearVelocityX(0);
    if (this->health > 100) {
        this->AnimateSpritePlayAnimation("ZombieAttackAnimation", false);
    }
    else if (this->health <= 100) {
        this->AnimateSpritePlayAnimation("ZombieLoseHeadAttackAnimation", false);
        this->SetSpriteWidth(10.000);
        this->SetSpriteHeight(11.875);
    }
}


void OrdinaryZombie::attacked_by(Arms* arm) {
    this->health -= arm->get_power();
    arm->after_hit();
    if (this->health <= 0) {
        this->die();
    }
}

/// <summary>
/// 被击倒后
/// </summary>
void OrdinaryZombie::die() {
    this->SetSpriteLinearVelocityX(0);
    this->AnimateSpritePlayAnimation("ZombieDieAnimation", false);
    this->SetSpriteCollisionActive(false, false);
    this->SetSpriteWidth(20.625);
    this->SetSpriteHeight(10.625);
    this->SetSpriteLifeTime(1);
}

int OrdinaryZombie::get_power() {
    return power;
}

OrdinaryZombie::~OrdinaryZombie() {
    std::cout << "~OrdinaryZombie()" << std::endl;
}