#pragma once
#include "PvZSprite.h"
class Assist :
    public PvZSprite
{
public:
    Assist(const char* sprite_name);
    const char* get_type() override;
protected:
    static const char* type;
};


class Range : public Assist {
public:
    Range(const char* assist_name);
    const char* get_type() override;
protected:
    static const char* type;
};

