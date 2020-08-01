#include "Assist.h"
const char* Assist::type = "Assist";
Assist::Assist(const char* sprite_name) :
    PvZSprite(sprite_name)
{
    this->exist = true;
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
/////////////////////////

const char* Car::type = "Car";
Car::Car(const char* assist_name) :
	Assist(assist_name)
{

}

const char* Car::get_type() {
	return type;
}

/////////////////////////

const char* Shovel::type = "Shovel";
bool Shovel::isSelected = false;
Shovel::Shovel(const char* assist_name) :
	Assist(assist_name)
{

}

const char* Shovel::get_type() {
	return type;
}

void Shovel::setSelected(bool is) {
	Shovel::isSelected = is;
}
bool Shovel::getSelected() {
	return Shovel::isSelected;
}
/////////////////////////
const char* PeaShooterCard::type = "PeaShooterCard";
PeaShooterCard::PeaShooterCard(const char* assist_name) :
    Assist(assist_name)
{

}

const char* PeaShooterCard::get_type() {
    return type;
}

///////////////////////

const char* SunflowerCard::type = "SunflowerCard";
SunflowerCard::SunflowerCard(const char* assist_name) :
    Assist(assist_name)
{

}

const char* SunflowerCard::get_type() {
    return type;
}

/////////////////////
const char* CherryBombCard::type = "CherryBombCard";
CherryBombCard::CherryBombCard(const char* assist_name) :
    Assist(assist_name)
{

}

const char* CherryBombCard::get_type() {
    return type;
}

/////////////////////
const char* Sun::type = "Sun";
Sun::Sun(const char* assist_name, int num) :
    Assist(assist_name),
    num(num)
{

}

const char* Sun::get_type() {
    return type;
}

/////////////////////
const char* WallNutCard::type = "WallNutCard";
WallNutCard::WallNutCard(const char* assist_name) :
    Assist(assist_name)
{

}

const char* WallNutCard::get_type() {
    return type;
}