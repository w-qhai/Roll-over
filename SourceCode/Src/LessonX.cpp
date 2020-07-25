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
	ord_zombie_count(5),
	t_ord_zombie(new OrdinaryZombie("OrdinaryZombie")),
	t_pea_shooter(new PeaShooter("PeaShooter", nullptr)),
	t_pea(new Pea("Pea")),
	t_range(new Range("PeaShooterAttackRange")),
	t_sunflower(new SunFlower("SunFlower"))
{

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
	int pos[5] = { -27, -12, 0, 12, 25 };
	for (int i = 0; i < ord_zombie_count; i++) {
		// 封装成 creat_zombie()
		OrdinaryZombie* zombie = new OrdinaryZombie(CSystem::MakeSpriteName("OrdinaryZombie", vec_ord_zombie.size()));
		vec_ord_zombie.push_back(zombie);
		name_to_sprite[zombie->GetName()] = zombie;
		zombie->CloneSprite(t_ord_zombie->GetName());
		zombie->SetSpritePosition(CSystem::GetScreenRight(), pos[i % 5]);
		zombie->move();
	}

	for (int i = 0; i < 5; i++) {
		// 封装成 creat_pea_shooter()
		Range* rect = new Range(CSystem::MakeSpriteName("PeaShooterAttackRange", vec_range.size()));
		vec_range.push_back(rect);
		name_to_sprite[rect->GetName()] = rect;
		rect->CloneSprite(t_range->GetName());

		Pea* pea = new Pea(CSystem::MakeSpriteName("Pea", vec_pea.size()));
		vec_pea.push_back(pea);
		name_to_sprite[pea->GetName()] = pea;

		PeaShooter* pshtr = new PeaShooter(CSystem::MakeSpriteName("PeaShooter", vec_pea_shooter.size()), pea);
		vec_pea_shooter.push_back(pshtr);
		name_to_sprite[pshtr->GetName()] = pshtr;

		pshtr->CloneSprite(t_pea_shooter->GetName());
		pshtr->SetSpritePosition(-40 + i * 15, pos[i] + 1);
		pshtr->SetSpriteImmovable(false);
		rect->SpriteMountToSprite(pshtr->GetName(), 11, 0);

		// 封装成 creat_sunflower()
		SunFlower* sf = new SunFlower(CSystem::MakeSpriteName("SunFlower", vec_sunflower.size()));
		std::cout << sf->get_type();
		vec_sunflower.push_back(sf);
		name_to_sprite[sf->GetName()] = sf;
		std::cout << t_sunflower->GetName() << std::endl;

		sf->CloneSprite(t_sunflower->GetName());
		sf->SetSpritePosition(-40 + i * 20, pos[i] + 1);
		sf->SetSpriteImmovable(false);
	}
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun(float fDeltaTime)
{
	timer += fDeltaTime;

	//for (PeaShooter* pshtr : vec_pea_shooter) {
	//	pshtr->attack(fDeltaTime);
	//}
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
	else {
		return nullptr;
	}
}