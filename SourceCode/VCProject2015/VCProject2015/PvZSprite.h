#pragma once
#include "CommonClass.h"

class PvZSprite : public CAnimateSprite
{
public:
    PvZSprite(const char* sprite_name);
    const virtual char* get_type() = 0;
private:
    char* type;
};

