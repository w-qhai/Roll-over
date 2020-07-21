#include "PeaShooter.h"
#include <iostream>
PeaShooter::PeaShooter(const char* plant_name) :
    Plant(plant_name, 200, 150),
    pea(new Pea("Pea"))
{
    
}

void PeaShooter::attack(float delta_time) {
    if ((next_attack -= delta_time) <= 0) {
        pea->SetSpriteLinearVelocityX(20);
        std::cout << "Shoot" << std::endl;
        next_attack = attack_interval;
    }
}