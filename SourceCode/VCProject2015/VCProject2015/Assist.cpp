#include "Assist.h"
const char* Assist::type = "Assist";
Assist::Assist(const char* sprite_name) :
    PvZSprite(sprite_name)
{

}

const char* Assist::get_type() {
    return type;
}

///////////////////////////

const char* Range::type = "Range";
Range::Range(const char* assist_name) :
    Assist(assist_name)
{

}

const char* Range::get_type() {
    return type;
}


/////////////////////////
///////////////////////////

const char* PeaShooterCard::type = "PeaShooterCard";
PeaShooterCard::PeaShooterCard(const char* assist_name) :
    Assist(assist_name)
{

}

const char* PeaShooterCard::get_type() {
    return type;
}