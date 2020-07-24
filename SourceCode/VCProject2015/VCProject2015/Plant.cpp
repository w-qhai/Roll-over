#include "Plant.h"

const char* Plant::type = "Plant";

Plant::Plant(const char* sprite_name, double health, int attack_interval) :
    PvZSprite(sprite_name),
    health(health), 
    next_attack(0),
    attack_interval(attack_interval) {

}

const char* Plant::get_type() {
    return type;
}

/* --------------------------------------------------- */
PeaShooter::PeaShooter(const char* plant_name, Pea* pea) :
    Plant(plant_name, 300, 2),
    pea(pea)
{
    
}

/// <summary>
/// 时间间隔积累到到一定程度后 开始进攻
/// </summary>
/// <param name="delta_time">每次时间间隔</param>
void PeaShooter::attack(float delta_time) {

    if ((next_attack -= delta_time) <= 0) {
        // 播放音乐： 发射豌豆(测试音效)
        SuperSound::closeAndPlay("open-shoot", "play-shoot", "close-shoot");
        pea->CloneSprite("Pea");
        std::cout << "shoot---" << std::endl;
        // 微调位置一下 从嘴部发出
        pea->SetSpritePosition(this->GetSpritePositionX() + 1, this->GetSpritePositionY() - 2);
        pea->SetSpriteLinearVelocityX(40);
        next_attack = attack_interval;
    }
}

/// <summary>
/// 植物被僵尸吃
/// </summary>
/// <param name="zombie">哪只僵尸</param>
/// <returns>true:被咬死； false：还没被咬死</returns>
bool PeaShooter::attacked_by(Zombie* zombie) {

    this->health -= zombie->get_power();
    std::cout << this->health << std::endl;
    if (this->health <= 0) {
        this->DeleteSprite();
        return true;
    }
    else {
        return false;
    }
}