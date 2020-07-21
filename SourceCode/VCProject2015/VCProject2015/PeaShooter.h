#pragma once
#include "Plant.h"
#include "Pea.h"

class PeaShooter : public Plant {

public:
    PeaShooter(const char* plant_name);
    void attack(float delta_time) override;
private:
    Pea* pea;
};

