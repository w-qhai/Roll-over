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
#undef min
#undef max
///////////////////////////////////////////////////////////////////////////////////////////
//
// 主函数入口
//
//////////////////////////////////////////////////////////////////////////////////////////

bool			left_pressed; // 鼠标左键是否按下
PvZSprite*		selected_card; // 选中的植物卡
PvZSprite*		seed;
bool exist_plant[10][5];
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
	if( !CSystem::InitGameEngine( hInstance, lpCmdLine ) )
		return 0;

	// To do : 在此使用API更改窗口标题
	CSystem::SetWindowTitle("PvZ");

	std::thread timer([&]() {
		while (true) {
			fTimeDelta += CSystem::GetTimeDelta();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	});
	timer.detach();

	// 引擎主循环，处理屏幕图像刷新等工作
	while( CSystem::EngineMainLoop() )
	{
		// 获取两次调用之间的时间差，传递给游戏逻辑处理

		// 执行游戏主循环
		g_GameMain.GameMainLoop( fTimeDelta );
	};

	// 关闭游戏引擎
	CSystem::ShutdownGameEngine();
	return 0;
}

//==========================================================================
//
// 引擎捕捉鼠标移动消息后，将调用到本函数
void CSystem::OnMouseMove( const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数
	if (left_pressed && selected_card && seed) {
		seed->SetSpritePosition(fMouseX, fMouseY);
	}
}
//==========================================================================
//
// 引擎捕捉鼠标点击消息后，将调用到本函数
void CSystem::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数
	if (iMouseType == MOUSE_LEFT) {
		left_pressed = true;
		selected_card = nullptr;
		seed = nullptr;

		selected_card = g_GameMain.get_sprite_by_position(fMouseX, fMouseY);
		if (selected_card) {
			std::cout << selected_card->GetName() << std::endl;
			if (selected_card->get_type() == "PeaShooterCard") {
				seed = g_GameMain.create_pea_shooter(fMouseX, fMouseY);
				seed->SetSpriteColorAlpha(100);
			}
		}
	}

}
//==========================================================================
//
// 引擎捕捉鼠标弹起消息后，将调用到本函数
void CSystem::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	float x_slot[10] = {-39, -28.5, -18, -7.5, 2, 12, 22, 32, 43, 55};
	float y_slot[5]  = { -17, -5, 9, 20, 32 };
	if (iMouseType == MOUSE_LEFT) {
		if (left_pressed && selected_card && seed) {
			seed->SetSpriteColorAlpha(255);

			// 确定位置
			int x = 0, y = 0;
			for (int i = 1; i < 10; i++) {
				if (abs(fMouseX - x_slot[x]) > abs(fMouseX - x_slot[i])) {
					x = i;
				}
			}
			for (int i = 1; i < 5; i++) {
				if (abs(fMouseY - y_slot[y] + seed->GetSpriteHeight() / 2) > abs(fMouseY - y_slot[i] + seed->GetSpriteHeight() / 2)) {
					y = i;
				}
			}
			// 如果鼠标最后位置有植物
			PvZSprite* sprite = g_GameMain.get_sprite_by_position(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
			std::cout << exist_plant[x][y] << std::endl;
			if (exist_plant[x][y] && sprite && sprite->is_exist()) {
				seed->DeleteSprite();
			}
			else {
				seed->SetSpritePosition(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
				exist_plant[x][y] = 1;
			}
		}
		left_pressed = false;
		selected_card = nullptr;
		seed = nullptr;
	}
}
//==========================================================================
//
// 引擎捕捉键盘按下消息后，将调用到本函数
// bAltPress bShiftPress bCtrlPress 分别为判断Shift，Alt，Ctrl当前是否也处于按下状态。比如可以判断Ctrl+E组合键
void CSystem::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
	// 可以在此添加游戏需要的响应函数
	
}
//==========================================================================
//
// 引擎捕捉键盘弹起消息后，将调用到本函数
void CSystem::OnKeyUp( const int iKey )
{
	// 可以在此添加游戏需要的响应函数

}

//===========================================================================
//
// 引擎捕捉到精灵与精灵碰撞之后，调用此函数
void CSystem::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	PvZSprite* src = g_GameMain.get_sprite_by_name(szSrcName);
	PvZSprite* tar = g_GameMain.get_sprite_by_name(szTarName);
	
	if (src && tar) {
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

		else if (src->get_type() == "Zombie" && tar->GetName() == "background") {
			Zombie* z = reinterpret_cast<Zombie*>(src);
			z->set_eating(false);
			std::cout << "background" << std::endl;
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
void CSystem::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	
}

