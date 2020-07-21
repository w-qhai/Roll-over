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