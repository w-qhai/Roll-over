#include "Zombie.h"

Zombie::Zombie() : CAnimateSprite("Zombie") {

}

void Zombie::move() {
    this->SetSpritePositionX(this->speed);
}

void Zombie::eat_plants() {

}

void Zombie::attacked() {

}

void Zombie::die() {

}