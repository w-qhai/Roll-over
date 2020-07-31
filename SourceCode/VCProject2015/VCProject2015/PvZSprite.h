#pragma once
#include "CommonClass.h"
#include <iostream>
#include <set>
class PvZSprite : public CAnimateSprite
{
public:
    PvZSprite(const char* sprite_name);
    const virtual char* get_type() = 0;
    bool is_exist() { return exist; }
    virtual void set_exist(bool exist) {}
protected:
    bool exist;
};

