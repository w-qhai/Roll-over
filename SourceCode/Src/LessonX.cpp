/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;

//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain() :
	m_iGameState(1),
	timer(0),
	sun_count(2000),
	game_map(new CSprite("background")),
	ord_zombie_count(5),
	t_ord_zombie(new OrdinaryZombie("OrdinaryZombie")),
	t_pea_shooter(new PeaShooter("PeaShooter", nullptr)),
	t_pea(new Pea("Pea")),
	t_range(new Range("PeaShooterAttackRange")),
	t_sunflower(new Sunflower("Sunflower")),
	pea_shooter_card(new PeaShooterCard("PeaShooterCard")), // 虚手动加入map
	sunflower_card(new SunflowerCard("SunflowerCard"))
{
	name_to_sprite[pea_shooter_card->GetName()] = pea_shooter_card;
	name_to_sprite[sunflower_card->GetName()] = sunflower_card;
}
//==============================================================================
//
// 析构函数
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态. 
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void CGameMain::GameMainLoop(float	fDeltaTime)
{
	switch (GetGameState())
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
	{
		GameInit();
		SetGameState(2); // 初始化之后，将游戏状态设置为进行中
	}
	break;

	// 游戏进行中，处理各种游戏逻辑
	case 2:
	{
		// TODO 修改此处游戏循环条件，完成正确游戏逻辑
		if (true)
		{
			GameRun(fDeltaTime);
		}
		else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
		{
			SetGameState(0);
			GameEnd();
		}
	}
	break;

	// 游戏结束/等待按空格键开始
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void CGameMain::GameInit()
{
	create_pea_shooter(-39, -5 + -17)->set_exist(true);
	create_pea_shooter(-39, -5 + -5)->set_exist(true);
	create_pea_shooter(-39, -5 + 9)->set_exist(true);
	create_pea_shooter(-39, -5 + 20)->set_exist(true);
	create_pea_shooter(-39, -5 + 32)->set_exist(true);
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
	if (fDeltaTime - timer > 3) {
		create_ord_zombie(CSystem::RandomRange(0, 4));
		timer = fDeltaTime;
	}
}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
}

// 用精灵名字映射精灵对象
PvZSprite* CGameMain::get_sprite_by_name(const std::string& sprite_name) {
	if (name_to_sprite.count(sprite_name)) {
		return name_to_sprite.at(sprite_name);
	}
	return nullptr;
}

PvZSprite* CGameMain::create_ord_zombie(int y) {
	float y_slot[5] = { -17, -5, 9, 20, 32 };
	OrdinaryZombie* zombie = new OrdinaryZombie(CSystem::MakeSpriteName(t_ord_zombie->GetName() , vec_ord_zombie.size()));
	vec_ord_zombie.push_back(zombie);
	name_to_sprite[zombie->GetName()] = zombie;
	zombie->CloneSprite(t_ord_zombie->GetName());
	zombie->set_exist(true);
	zombie->SetSpritePosition(CSystem::GetScreenRight(), y_slot[y] - zombie->GetSpriteHeight() / 2);
	zombie->move();

	return zombie;
}

PvZSprite* CGameMain::create_pea_shooter(float x, float y) {
	// 创建豌豆射手的 攻击范围
	Range* rect = new Range(CSystem::MakeSpriteName(t_range->GetName(), vec_range.size()));
	vec_range.push_back(rect);
	name_to_sprite[rect->GetName()] = rect;
	rect->CloneSprite(t_range->GetName());
	rect->set_exist(true);

	// 创建豌豆射手的 豌豆
	Pea* pea = new Pea(CSystem::MakeSpriteName("Pea", vec_pea.size()));
	vec_pea.push_back(pea);
	name_to_sprite[pea->GetName()] = pea;
	pea->set_exist(false);

	// 创建豌豆射手
	PeaShooter* pshtr = new PeaShooter(CSystem::MakeSpriteName(t_pea_shooter->GetName(), vec_pea_shooter.size()), pea);
	vec_pea_shooter.push_back(pshtr);
	name_to_sprite[pshtr->GetName()] = pshtr;

	pshtr->CloneSprite(t_pea_shooter->GetName());
	pshtr->SetSpritePosition(x, y);
	pshtr->SetSpriteImmovable(false);
	rect->SpriteMountToSprite(pshtr->GetName(), 11, -0.5);
	pshtr->set_exist(false);
	return pshtr;
}

PvZSprite* CGameMain::create_sunflower(float x, float y) {

	Sunflower* sf = new Sunflower(CSystem::MakeSpriteName(t_sunflower->GetName(), vec_sunflower.size()));
	std::cout << sf->get_type();
	vec_sunflower.push_back(sf);
	name_to_sprite[sf->GetName()] = sf;
	std::cout << t_sunflower->GetName() << std::endl;

	sf->CloneSprite(t_sunflower->GetName());
	sf->SetSpritePosition(x, y);
	sf->SetSpriteImmovable(false);
	sf->set_exist(false);
	return sf;
}

PvZSprite* CGameMain::get_sprite_by_position(float x, float y) {
	for (std::pair<std::string, PvZSprite*> sprite : name_to_sprite) {
		if (sprite.second->IsPointInSprite(x, y)) {
			return sprite.second;
		}
	}
	return nullptr;
}