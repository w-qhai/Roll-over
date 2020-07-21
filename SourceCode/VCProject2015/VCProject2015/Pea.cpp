#include "Pea.h"

Pea::Pea(const char* arms_name) :
    Arms(arms_name, 30)
{

}

void Pea::boom() {
    this->AnimateSpritePlayAnimation("PeaBulletHitAnimation", true);
}