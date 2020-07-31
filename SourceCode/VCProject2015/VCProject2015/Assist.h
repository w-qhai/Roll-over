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

class Sun : public Assist {
public:
    Sun(const char* assist_name, int num);
    const char* get_type() override;
    int get_num() { return num; }
protected:
    int num;
    static const char* type;
};

class WallNutCard : public Assist {
public:
    WallNutCard(const char* assist_name);
    const char* get_type() override;
protected:
    static const char* type;
};
