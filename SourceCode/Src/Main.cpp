//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonClass.h"
#include "LessonX.h"
#include "../VCProject2015/VCProject2015/Timer.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <functional>
#undef min
#undef max
///////////////////////////////////////////////////////////////////////////////////////////
//
// 主函数入口
//
//////////////////////////////////////////////////////////////////////////////////////////

bool			left_pressed; // 鼠标左键是否按下
int				map_id = 0;				 // 当前地图 0:welcome; 1:menu; 2:关卡
Card*			card;		// 植物卡
Plant*			seed;		// 植物种子
Shovel*			shovel; // 选中了小铲子
long double 	fTimeDelta;
int PASCAL WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	//开启控制台，方便调试信息输出
	FILE* stream;
	AllocConsole();
	freopen_s(&stream, "CONOUT$", "a+", stdout);

	// 初始化游戏引擎
	if (!CSystem::InitGameEngine(hInstance, lpCmdLine))
		return 0;

	// To do : 在此使用API更改窗口标题
	CSystem::SetWindowTitle("PvZ");
	//CSystem::LoadMap("welcome.t2d");

	std::thread timer([&]() {
		while (true) {
			fTimeDelta += CSystem::GetTimeDelta();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		});
	timer.detach();

	// 引擎主循环，处理屏幕图像刷新等工作
	while (CSystem::EngineMainLoop())
	{
		// 获取两次调用之间的时间差，传递给游戏逻辑处理
		// 执行游戏主循环
		g_GameMain.GameMainLoop(fTimeDelta);
	};

	// 关闭游戏引擎
	CSystem::ShutdownGameEngine();
	return 0;
}

//==========================================================================
//
// 引擎捕捉鼠标移动消息后，将调用到本函数
// 菜单界面地图 鼠标移动 event handler
static void menu_map_OnMouseMove(const float fMouseX, const float fMouseY) {
	CAnimateSprite adcenture("AdventureGame"); // 冒险模式
	CAnimateSprite mini("MiniGame");		   // 迷你游戏
	CAnimateSprite edu("EduGame");			   // 益智模式
	if (adcenture.IsPointInSprite(fMouseX, fMouseY)) {
		adcenture.AnimateSpritePlayAnimation("AdventureModeAnimation", false);
	}
	if (mini.IsPointInSprite(fMouseX, fMouseY)) {
		mini.AnimateSpritePlayAnimation("MiniModeAnimation", false);
	}
	if (edu.IsPointInSprite(fMouseX, fMouseY)) {
		edu.AnimateSpritePlayAnimation("EduModeAnimation", false);
	}

}
void CSystem::OnMouseMove(const float fMouseX, const float fMouseY)
{
	// 不同地图间点击事件分别封装，根据全局的地图id区分不同地图的事件
	switch (map_id)
	{
	case 0:
		break;
	case 1:
		menu_map_OnMouseMove(fMouseX, fMouseY);
	default:
		break;
	}
	// 可以在此添加游戏需要的响应函数
	if (left_pressed && shovel) {
		shovel->SetSpritePosition(fMouseX, fMouseY);
	}
	else if (left_pressed && seed) {
		seed->SetSpritePosition(fMouseX, fMouseY);
	}
}
// 对不同地图间的事件进行分离, 以便保证不同地图相同区域点击事件的不会冲突
// 欢迎界面地图 鼠标点击 event handler
static void welcome_map_OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	CSprite startBtn("LoadBar");
	if (iMouseType == MOUSE_LEFT) {
		if (startBtn.IsPointInSprite(fMouseX, fMouseY)) {
			CSystem::LoadMap("menu.t2d");
			map_id = 1;
		}
	}
}
// 菜单界面地图 鼠标点击 event handler
static void menu_map_OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	CSprite adcenture("AdventureGame");
	if (iMouseType == MOUSE_LEFT) {
		if (adcenture.IsPointInSprite(fMouseX, fMouseY)) {
			CSystem::LoadMap("level.t2d");
			map_id = 2;
		}
	}
}
//==========================================================================
//
// 引擎捕捉鼠标点击消息后，将调用到本函数
void CSystem::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY)
{
	// 不同地图间点击事件分别封装，根据全局的地图id区分不同地图的事件
	switch (map_id)
	{
	case 0:
		welcome_map_OnMouseClick(iMouseType, fMouseX, fMouseY);
	case 1:
		menu_map_OnMouseClick(iMouseType, fMouseX, fMouseY);
	default:
		break;
	}

	// 可以在此添加游戏需要的响应函数
	if (iMouseType == MOUSE_LEFT) {

		left_pressed = true;
		card = nullptr;
		seed = nullptr;
		shovel = nullptr;
		// selected_card = g_GameMain.get_sprite_by_position(fMouseX, fMouseY);
		// 右值引用 提高效率
		std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(fMouseX, fMouseY);

		for (const auto& sprite : sprites) {
			// 选中的位置有太阳
			if (sprite->get_type() == "Sun") {
				Sun* sun = reinterpret_cast<Sun*>(sprite);
				sun->SpriteMoveTo(-43.275, -33.275, 100, true);
				sun->SetSpriteLifeTime(1);
				g_GameMain.add_sun(sun->get_num());
				sun->set_exist(false);

				left_pressed = false;
				break;
			}

			// 选中的位置有小车，不做任何事情
			if (sprite->get_type() == "Car") {
				continue;
			}

			// 选中铲子
			if (sprite->get_type() == "Shovel") {
				shovel = reinterpret_cast<Shovel*>(sprite);
				break;
			}

			// 选中卡片
			std::string type = sprite->get_type();
			// 后四位Card表示 植物卡
			if (type.substr(type.size() - 4, 4) == "Card") {
				// 鼠标按下 选中植物卡
				card = reinterpret_cast<Card*>(sprite);
				// 如果选中的卡 冷却完毕
				if (card->ready(fTimeDelta)) {
					if (sprite->get_type() == "PeaShooterCard") {
						seed = g_GameMain.create_pea_shooter(fMouseX, fMouseY);
					}
					else if (sprite->get_type() == "SunflowerCard") {
						seed = g_GameMain.create_sunflower(fMouseX, fMouseY);
					}
					else if (sprite->get_type() == "CherryBombCard") {
						seed = g_GameMain.create_cherry_bomb(fMouseX, fMouseY);
					}
					else if (sprite->get_type() == "WallNutCard") {
						seed = g_GameMain.create_wall_nut(fMouseX, fMouseY);
					}
					std::cout << card->GetName() << " ready" << std::endl;
					seed->SetSpriteColorAlpha(100);
				}
				else {
					std::cout << card->GetName() << " not ready" << std::endl;
					card = nullptr;
				}
				break;
			}
		}
	}
}
//==========================================================================
//
// 引擎捕捉鼠标弹起消息后，将调用到本函数
void CSystem::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY)
{
	float x_slot[10] = { -39, -28.5, -18, -7.5, 2, 12, 22, 32, 43, 55 };
	float y_slot[5] = { -17, -5, 9, 20, 32 };

	int x = 0, y = 0;
	for (int i = 1; i < 10; i++) {
		if (abs(fMouseX - x_slot[x]) > abs(fMouseX - x_slot[i])) {
			x = i;
		}
	}
	if (iMouseType == MOUSE_LEFT) {
		// 确定位置
		if (left_pressed && seed && card) {
			for (int i = 1; i < 5; i++) {
				if (abs(fMouseY - y_slot[y] + seed->GetSpriteHeight() / 2) > abs(fMouseY - y_slot[i] + seed->GetSpriteHeight() / 2)) {
					y = i;
				}
			}
			std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
			seed->SetSpriteColorAlpha(255);
			bool planting = true;

			// 如果位置中有植物 或 僵尸，则不能种
			for (const auto& sprite : sprites) {
				if (sprite->get_type() == "Plant") {
					planting = false;
					break;
				}

				if (sprite->get_type() == "Plant") {
					if (card->get_type() == "CherryBombCard") {
						planting = true;
					}
					else {
						planting = false;
					}
					break;
				}
			}

			if (planting && g_GameMain.planting(seed) && card) {
				seed->SetSpritePosition(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
				seed->set_exist(true);
				card->plant_time(fTimeDelta);
			}
			else {
				seed->DeleteSprite();
			}
		}
		else if (left_pressed && shovel) {
			for (int i = 1; i < 5; i++) {
				if (abs(fMouseY - y_slot[y] + shovel->GetSpriteHeight() / 2) > abs(fMouseY - y_slot[i] + shovel->GetSpriteHeight() / 2)) {
					y = i;
				}
			}
			std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(x_slot[x], y_slot[y] - shovel->GetSpriteHeight() / 2);

			// 位置上有植物 挖走
			for (const auto& sprite : sprites) {
				if (sprite->get_type() == "Plant") {
					Plant* p = reinterpret_cast<Plant*>(sprite);
					p->die();
					break;
				}
			}
			shovel->SetSpritePosition(12.093, -32.500);
		}
		left_pressed = false;
		seed = nullptr;
		shovel = nullptr;
	}
}
//==========================================================================
//
// 引擎捕捉键盘按下消息后，将调用到本函数
// bAltPress bShiftPress bCtrlPress 分别为判断Shift，Alt，Ctrl当前是否也处于按下状态。比如可以判断Ctrl+E组合键
void CSystem::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress)
{
	// 可以在此添加游戏需要的响应函数

}
//==========================================================================
//
// 引擎捕捉键盘弹起消息后，将调用到本函数
void CSystem::OnKeyUp(const int iKey)
{
	// 可以在此添加游戏需要的响应函数

}

//===========================================================================
//
// 引擎捕捉到精灵与精灵碰撞之后，调用此函数
void CSystem::OnSpriteColSprite(const char* szSrcName, const char* szTarName)
{
	PvZSprite* src = g_GameMain.get_sprite_by_name(szSrcName);
	PvZSprite* tar = g_GameMain.get_sprite_by_name(szTarName);


	if (src && tar) {

		// 小车启动
		if (src->get_type() == "Car" && tar->get_type() == "Zombie") {

			std::cout << "src:" << src->get_type() << "  tar:" << tar->get_type() << std::endl;

			Zombie* z = reinterpret_cast<Zombie*>(tar);  // 指针强转
			Car* c = reinterpret_cast<Car*>(src);  // 指针强转

			c->SetSpriteLinearVelocityX(25.0);

			z->die(0);

		}

		// 僵尸进入攻击范围
		if (src->get_type() == "Range" && tar->get_type() == "Zombie") {
			// 转换成其父精灵的指针
			PvZSprite* pvz = g_GameMain.get_sprite_by_name(src->GetSpriteMountedParent());
			Plant* p = reinterpret_cast<Plant*>(pvz);
			p->attack(fTimeDelta);
		}

		// 僵尸吃植物
		if (src->get_type() == "Zombie" && tar->get_type() == "Plant") {
			Zombie* z = reinterpret_cast<Zombie*>(src);  // 指针强转
			Plant* p = reinterpret_cast<Plant*>(tar);
			z->eat_plant(p, fTimeDelta);
		}

		// 子弹打僵尸
		if (src->get_type() == "Arms" && tar->get_type() == "Zombie") {
			Arms* a = reinterpret_cast<Arms*>(src);  // 指针强转
			Zombie* z = reinterpret_cast<Zombie*>(tar);
			z->attacked_by(a);
		}
	}
}

//===========================================================================
//
// 引擎捕捉到精灵与世界边界碰撞之后，调用此函数.
// iColSide : 0 左边，1 右边，2 上边，3 下边
void CSystem::OnSpriteColWorldLimit(const char* szName, const int iColSide)
{

}

