#include "PvZSprite.h"
PvZSprite::PvZSprite(const char* sprite_name) :
    CAnimateSprite(sprite_name),
    exist(false)
{

}

void PvZSprite::set_exist(bool exist) {
    this->exist = exist; 
    this->SetSpriteCollisionSend(exist);
    this->SetSpriteCollisionReceive(exist);
    this->SetSpriteCollisionPhysicsReceive(exist);
    this->SetSpriteCollisionPhysicsSend(exist);
}