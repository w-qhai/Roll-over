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

class PeaShooterCard : public Assist {
public:
    PeaShooterCard(const char* assist_name);
    const char* get_type() override;
protected:
    static const char* type;
};

class SunflowerCard : public Assist {
public:
    SunflowerCard(const char* assist_name);
    const char* get_type() override;
protected:
    static const char* type;
};

class CherryBombCard : public Assist {
public:
    CherryBombCard(const char* assist_name);
    const char* get_type() override;
protected:
    static const char* type;
};


