#pragma once
#include "PvZSprite.h"
// ��������
class Arms : public PvZSprite {
public:
    Arms(const char* sprite_name, int power);
    virtual void after_hit() = 0;
    const char* get_type() override;
protected:
    int power;
    static const char* type;
};


// �㶹 �̳�������
class Pea : public Arms
{
public:
    Pea(const char* arms_name);
    void after_hit() override;
};


