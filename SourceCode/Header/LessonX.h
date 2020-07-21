/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../VCProject2015/VCProject2015/OrdinaryZombie.h"
#include "../VCProject2015/VCProject2015/PeaShooter.h"
#include "../VCProject2015/VCProject2015/Pea.h"
/////////////////////////////////////////////////////////////////////////////////
//
// 游戏总管类。负责处理游戏主循环、游戏初始化、结束等工作
class	CGameMain
{
private:
	int				m_iGameState;				// 游戏状态，0：结束或者等待开始；1：初始化；2：游戏进行中
	std::map<std::string, PvZSprite*>	name_to_sprite;
	float			timer;						// 游戏运行时间

	std::vector<OrdinaryZombie*> vec_ord_zombie;
	std::vector<PeaShooter*> vec_pea_shooter;

	// 精灵模板
	OrdinaryZombie* t_ord_zombie;
	PeaShooter* t_pea_shooter;
	Pea* pea;
public:
	CGameMain();            //构造函数
	~CGameMain();           //析构函数  

	// Get方法
	int				GetGameState()											{ return m_iGameState; }
	
	// Set方法
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }
	
	// 游戏主循环等
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();
	PvZSprite* get_sprite_by_name(const std::string& sprite_name);
};

/////////////////////////////////////////////////////////////////////////////////
// 
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_