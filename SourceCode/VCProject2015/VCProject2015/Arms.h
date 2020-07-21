#pragma once
#include "PvZSprite.h"
class Arms : public PvZSprite {
public:
    Arms(const char* sprite_name, int power);
    const char* get_type() override;
protected:
    int power;
    static const char* type;
};

