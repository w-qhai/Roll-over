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
#include "../VCProject2015/VCProject2015/Zombie.h"
#include "../VCProject2015/VCProject2015/Plant.h"
#include "../VCProject2015/VCProject2015/Assist.h"

/////////////////////////////////////////////////////////////////////////////////
//
// 游戏总管类。负责处理游戏主循环、游戏初始化、结束等工作
class	CGameMain
{
private:
	int				m_iGameState;				// 游戏状态，0：结束或者等待开始；1：初始化；2：游戏进行中
	long double		timer;						// 游戏运行时间

	std::map<std::string, PvZSprite*>	name_to_sprite;
	// 阳光数量
	int sun_count;
	CTextSprite* sun_num;
	// 地图精灵
	CSprite* game_map;

	// 精灵数量
	int ord_zombie_count;

	// 精灵容器
	std::vector<Car*>               vec_car;
	std::vector<OrdinaryZombie*>	vec_ord_zombie;
	std::vector<BarricadeZombie*>	vec_bar_zombie;
	std::vector<BucketheadZombie*>	vec_buc_zombie;
	std::vector<NewspaperZombie*>	vec_new_zombie;
	std::vector<FootballZombie*>	vec_fot_zombie;

	std::vector<Pea*>				vec_pea;
	std::vector<PeaShooter*>		vec_pea_shooter;
	std::vector<Range*>				vec_range;
	std::vector<Sunflower*>			vec_sunflower;
	std::vector<CherryBomb*>		vec_cherry_bomb;
	std::vector<Boom*>				vec_boom;
	std::vector<Sun*>				vec_sun;
	std::vector<WallNut*>			vec_wall_nut;
	std::vector<PotatoMine*>		vec_potato_mine;
	std::vector<Jalapeno*>			vec_jalapeno;
	std::vector<Card*>				vec_card;

	// 小车 铲子
	Car* tool_car;
	Shovel* tool_shovel;

	OrdinaryZombie* t_ord_zombie;
	BarricadeZombie* t_bar_zombie;
	BucketheadZombie* t_buc_zombie;
	NewspaperZombie* t_new_zombie;
	FootballZombie* t_fot_zombie;
	PeaShooter* t_pea_shooter;
	Pea* t_pea;
	Boom* t_boom;
	Range* t_range;
	Sunflower* t_sunflower;
	CherryBomb* t_cherry_bomb;
	Sun* t_sun;
	WallNut* t_wall_nut;
	PotatoMine* t_potato_mine;
	Jalapeno* t_jalapeno;

	// 植物卡
	PeaShooterCard* pea_shooter_card;
	SunflowerCard* sunflower_card;
	CherryBombCard* cherry_bomb_card;
	PotatoMineCard* potato_mine_card;
	WallNutCard* wall_nut_card;
	JalapenoCard* jalapeno_card;

public:
	CGameMain();            //构造函数
	~CGameMain();           //析构函数  

	// Get方法
	int				GetGameState()											{ return m_iGameState; }

	// Set方法
	void			SetGameState( const int iState )						{ m_iGameState = iState; }

	// 游戏主循环等
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();
	PvZSprite* get_sprite_by_name(const std::string& sprite_name);
	std::vector<PvZSprite*> get_sprites_by_position(float x, float y);
	Zombie* create_ord_zombie(int y);
	Zombie* create_bar_zombie(int y);
	Zombie* create_buc_zombie(int y);
	Zombie* create_new_zombie(int y);
	Zombie* create_fot_zombie(int y);

	Car* create_car(float x, float y);
	Plant*	create_pea_shooter(float x, float y);
	Plant*	create_sunflower(float x, float y);
	Plant*	create_cherry_bomb(float x, float y, long double plant_time);
	Plant*	create_wall_nut (float x, float y);
	Plant*	create_potato_mine(float x, float y, long double plant_time);
	Plant*	create_jalapeno(float x, float y, long double plant_time);
	void create_gray_mask(Card* card);
	bool	planting(Plant* plant);
	void	output_sun(int num = 25);	// 空值则由场景产出，否则为植物产出
	void	add_sun(int num);
};

/////////////////////////////////////////////////////////////////////////////////
// 
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_