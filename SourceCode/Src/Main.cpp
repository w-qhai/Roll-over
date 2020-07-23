//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonClass.h"
#include "LessonX.h"
#include <iostream>
///////////////////////////////////////////////////////////////////////////////////////////
//
// 主函数入口
//
//////////////////////////////////////////////////////////////////////////////////////////
float	fTimeDelta;
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

	// 引擎主循环，处理屏幕图像刷新等工作
	while( CSystem::EngineMainLoop() )
	{
		// 获取两次调用之间的时间差，传递给游戏逻辑处理
		float	fTimeDelta	=	CSystem::GetTimeDelta();

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

}
//==========================================================================
//
// 引擎捕捉鼠标点击消息后，将调用到本函数
void CSystem::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数

}
//==========================================================================
//
// 引擎捕捉鼠标弹起消息后，将调用到本函数
void CSystem::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数

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
		if (src->get_type() == "Range" && tar->get_type() == "Zombie") {
			// 转换成其父精灵的指针
			PvZSprite* pvz = g_GameMain.get_sprite_by_name(src->GetSpriteMountedParent());
			Plant* p = reinterpret_cast<Plant*>(pvz);
			p->attack(0.03);
		}

		// 僵尸吃植物
		if (src->get_type() == "Zombie" && tar->get_type() == "Plant") {
			//std::cout << szSrcName << " " << szTarName << std::endl;
			Zombie* z = reinterpret_cast<Zombie*>(src);  // 指针强转
			Plant* p = reinterpret_cast<Plant*>(tar);
			//z->stop();
			if (!z->is_eating()) {
				z->eat_plant();
			}
			if (p->attacked_by(z)) {
				z->move();
			}		
		}

		// 子弹打僵尸
		if (src->get_type() == "Arms" && tar->get_type() == "Zombie") {
			//std::cout << szSrcName << " " << szTarName << std::endl;
			Arms* a = reinterpret_cast<Arms*>(src);  // 指针强转
			Zombie* z = reinterpret_cast<Zombie*>(tar);
			a->after_hit();
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

