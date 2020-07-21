#include "Arms.h"
const char* Arms::type = "Arms";
Arms::Arms(const char* sprite_name, int power) :
    PvZSprite(sprite_name),
    power(power)
{

}

const char* Arms::get_type() {
    return type;
}
