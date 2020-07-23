#include "Zombie.h"

const char* Zombie::type = "Zombie";

Zombie::Zombie(const char* sprite_name, int health, int move_speed, double power) :
    PvZSprite(sprite_name),
    health(health),
    move_speed(move_speed),
    power(power),
    next_attack(0),
    attack_interval(500),
    eating(false)
{

}

const char* Zombie::get_type() {
    return type;
}
bool Zombie::is_eating() {
    return eating;
}

/////////////////////////

OrdinaryZombie::OrdinaryZombie(const char* zombie_name) :
    Zombie(zombie_name, 200, 3, 0.5)
{

}

/// <summary>
/// 让僵尸开始移动
/// </summary>
void OrdinaryZombie::move() {
    this->eating = false;
    this->set_status();
    this->SetSpriteLinearVelocityX(-this->move_speed);
}

void OrdinaryZombie::stop() {
    this->set_status();
    this->SetSpriteLinearVelocityX(0);
}

void OrdinaryZombie::eat_plant() {
    eating = true;
    if (this->health > 100) {
        this->AnimateSpritePlayAnimation("ZombieAttackAnimation", false);
    }
    else if (this->health <= 100) {
        this->AnimateSpritePlayAnimation("ZombieLoseHeadAttackAnimation", false);
        this->SetSpriteWidth(10.000);
        this->SetSpriteHeight(11.875);
    }
}


void OrdinaryZombie::attacked_by(Arms* arms) {
    this->health -= arms->get_power();
    arms->after_hit();
    if (this->health <= 0) {
        this->die();
    }
    else {
        this->set_status();
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
    // 播放死亡动画
    this->SetSpriteLifeTime(1);
}

double OrdinaryZombie::get_power() {
    return power;
}

OrdinaryZombie::~OrdinaryZombie() {
    std::cout << "~OrdinaryZombie()" << std::endl;
}

void OrdinaryZombie::set_status() {
    if (this->health > 100) {
        if (eating) {
            this->AnimateSpritePlayAnimation("ZombieAttackAnimation", false);
        }
        else {
            this->AnimateSpritePlayAnimation("OrdinaryZombieAnimation", false);
        }
    }
    else if (this->health <= 100) {
        if (eating) {
            this->AnimateSpritePlayAnimation("ZombieLoseHeadAttackAnimation", false);
        }
        else {
            this->AnimateSpritePlayAnimation("ZombieLoseHeadAnimation", false);
            this->SetSpriteWidth(10.000);
            this->SetSpriteHeight(11.875);
        }
    }
}