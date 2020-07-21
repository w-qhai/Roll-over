#include "OrdinaryZombie.h"
OrdinaryZombie::OrdinaryZombie(const char* zombie_name) :
    Zombie(zombie_name, 200, 10)
{
    
}

void OrdinaryZombie::move() {
    this->SetSpriteLinearVelocityX(-this->move_speed);
}

void OrdinaryZombie::eat_plant() {

}

void OrdinaryZombie::die() {
    this->AnimateSpritePlayAnimation("BoomDieAnimation", false);
}
