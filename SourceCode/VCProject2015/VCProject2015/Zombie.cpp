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