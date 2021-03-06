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
	sun_count(20000),
	sun_num(new CTextSprite("SunCount")),
	game_map(new CSprite("background")),
	ord_zombie_count(5),

	// 模板初始化
	t_ord_zombie(new OrdinaryZombie("OrdinaryZombie")),
	t_bar_zombie(new BarricadeZombie("BarricadeZombie")),
	t_buc_zombie(new BucketheadZombie("BucketheadZombie")),
	t_new_zombie(new NewspaperZombie("NewspaperZombie")),
	t_fot_zombie(new FootballZombie("FootballZombie")),
	t_pea_shooter(new PeaShooter("PeaShooter", nullptr)),
	t_pea(new Pea("Pea")),
	t_range(new Range("AttackRange")),
	t_sun(new Sun("Sun", 25)),
	t_sunflower(new Sunflower("Sunflower", nullptr)),
	t_boom(new Boom("Boom")),
	t_cherry_bomb(new CherryBomb("CherryBomb", nullptr, 0)),
	t_wall_nut(new WallNut("WallNut")),
	t_potato_mine(new PotatoMine("PotatoMine", nullptr, 0)),
	t_jalapeno(new Jalapeno("Jalapeno", nullptr, 0)),

	// 小车初始化
	tool_car(new Car("Car")),
	tool_shovel(new Shovel("Shovel")),
	// 卡初始化
	pea_shooter_card(new PeaShooterCard("PeaShooterCard")), // 虚手动加入map
	sunflower_card(new SunflowerCard("SunflowerCard")),
	cherry_bomb_card(new CherryBombCard("CherryBombCard")),
	potato_mine_card(new PotatoMineCard("PotatoMineCard")),
	wall_nut_card(new WallNutCard("WallNutCard")),
	jalapeno_card(new JalapenoCard("JalapenoCard"))
{
	name_to_sprite[pea_shooter_card->GetName()] = pea_shooter_card;
	vec_card.push_back(pea_shooter_card);

	name_to_sprite[sunflower_card->GetName()] = sunflower_card;
	vec_card.push_back(sunflower_card);
	
	name_to_sprite[cherry_bomb_card->GetName()] = cherry_bomb_card;
	vec_card.push_back(cherry_bomb_card);
	
	name_to_sprite[wall_nut_card->GetName()] = wall_nut_card;
	vec_card.push_back(wall_nut_card);

	name_to_sprite[potato_mine_card->GetName()] = potato_mine_card;
	vec_card.push_back(potato_mine_card);

	name_to_sprite[jalapeno_card->GetName()] = jalapeno_card;
	vec_card.push_back(jalapeno_card);

	name_to_sprite[tool_shovel->GetName()] = tool_shovel;
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
	//pea_shooter_card(new PeaShooterCard("PeaShooterCard")), // 虚手动加入map
	//sunflower_card(new SunflowerCard("SunflowerCard")),
	//(new CherryBombCard("CherryBombCard")),
	//wall_nut_card(new WallNutCard("WallNutCard"))
	create_gray_mask(pea_shooter_card);
	create_gray_mask(sunflower_card);
	create_gray_mask(cherry_bomb_card);
	create_gray_mask(potato_mine_card);
	create_gray_mask(wall_nut_card);
	create_gray_mask(jalapeno_card);


	// welcome.t2d
	CSprite title("Title");
	title.SpriteMoveTo(-0.909, -27.080, 18, true);

	CSprite load("load");
	load.SetSpriteAngularVelocity(80);
	load.SpriteMoveTo(0.75 + 41.5 / 2 - 6, 30.875 - 11.75 / 2 + 2.7, 10, true);
	load.SetSpriteLifeTime(4);

	create_car(-47.5, -5 + -17)->set_exist(true);
	create_car(-47.5, -5 + -5)->set_exist(true);
	create_car(-47.5, -5 + 9)->set_exist(true);
	create_car(-47.5, -5 + 20)->set_exist(true);
	create_car(-47.5, -5 + 32)->set_exist(true);
	create_fot_zombie(1);
	create_fot_zombie(2);
	create_fot_zombie(3);
	create_fot_zombie(4);
	sun_num->SetTextValue(sun_count);
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun(float fDeltaTime)
{
	// menu.t2d
	//CSprite welcome("welcome");
	//welcome.SpriteMoveTo(-28.883, -23.750, 18, true);

	


	if (fDeltaTime - timer > 4) {

		
		timer = fDeltaTime;
		output_sun();
	}


	// 向日葵产生阳光
	for (Sunflower* sunflower : vec_sunflower) {
		if (sunflower->is_exist()) {
			sunflower->attack(fDeltaTime);
		}
	}

	// 唤醒土豆
	for (PotatoMine* pm : vec_potato_mine) {
		if (pm->is_exist()) {
			pm->preparation(fDeltaTime);
		}
	}

	// 樱桃爆炸
	for (CherryBomb* cb : vec_cherry_bomb) {
		if (cb->is_exist()) {
			cb->preparation(fDeltaTime);
		}
	}

	// 樱桃爆炸
	for (Jalapeno* jp : vec_jalapeno) {
		if (jp->is_exist()) {
			jp->preparation(fDeltaTime);
		}
	}

	for (Card* card : vec_card) {
		card->ready(fDeltaTime);
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
Car* CGameMain::create_car(float x, float y) {
	Car* car = new Car(CSystem::MakeSpriteName("Car", vec_car.size()));
	vec_car.push_back(car);
	name_to_sprite[car->GetName()] = car;

	car->CloneSprite(tool_car->GetName());
	car->SetSpritePosition(x, y);
	return car;
}


Zombie* CGameMain::create_ord_zombie(int y) {
	float y_slot[5] = { -17, -5, 9, 20, 32 };
	OrdinaryZombie* zombie = new OrdinaryZombie(CSystem::MakeSpriteName(t_ord_zombie->GetName(), vec_ord_zombie.size()));
	vec_ord_zombie.push_back(zombie);
	name_to_sprite[zombie->GetName()] = zombie;
	zombie->CloneSprite(t_ord_zombie->GetName());
	zombie->set_exist(true);
	zombie->SetSpritePosition(CSystem::GetScreenRight(), y_slot[y] - zombie->GetSpriteHeight() / 2);
	zombie->move();

	return zombie;
}
//BarricadeZombie
Zombie* CGameMain::create_bar_zombie(int y) {
	float y_slot[5] = { -17, -5, 9, 20, 32 };
	BarricadeZombie* zombie = new BarricadeZombie(CSystem::MakeSpriteName(t_bar_zombie->GetName(), vec_bar_zombie.size()));
	vec_bar_zombie.push_back(zombie);
	name_to_sprite[zombie->GetName()] = zombie;
	zombie->CloneSprite(t_bar_zombie->GetName());
	zombie->set_exist(true);
	zombie->SetSpritePosition(CSystem::GetScreenRight(), y_slot[y] - zombie->GetSpriteHeight() / 2);
	zombie->move();

	return zombie;
}


//BucketheadZombie
Zombie* CGameMain::create_buc_zombie(int y) {
	float y_slot[5] = { -17, -5, 9, 20, 32 };
	BucketheadZombie* zombie = new BucketheadZombie(CSystem::MakeSpriteName(t_buc_zombie->GetName(), vec_buc_zombie.size()));
	vec_buc_zombie.push_back(zombie);
	name_to_sprite[zombie->GetName()] = zombie;
	zombie->CloneSprite(t_buc_zombie->GetName());
	zombie->set_exist(true);
	zombie->SetSpritePosition(CSystem::GetScreenRight(), y_slot[y] - zombie->GetSpriteHeight() / 2);
	zombie->move();

	return zombie;
}

Zombie* CGameMain::create_new_zombie(int y) {
	float y_slot[5] = { -17, -5, 9, 20, 32 };
	NewspaperZombie* zombie = new NewspaperZombie(CSystem::MakeSpriteName(t_new_zombie->GetName(), vec_new_zombie.size()));
	vec_new_zombie.push_back(zombie);
	name_to_sprite[zombie->GetName()] = zombie;
	zombie->CloneSprite(t_new_zombie->GetName());
	zombie->set_exist(true);
	zombie->SetSpritePosition(CSystem::GetScreenRight(), y_slot[y] - zombie->GetSpriteHeight() / 2);
	zombie->move();

	return zombie;
}

Zombie* CGameMain::create_fot_zombie(int y) {
	float y_slot[5] = { -17, -5, 9, 20, 32 };
	FootballZombie* zombie = new FootballZombie(CSystem::MakeSpriteName(t_fot_zombie->GetName(), vec_fot_zombie.size()));
	vec_fot_zombie.push_back(zombie);
	name_to_sprite[zombie->GetName()] = zombie;
	zombie->CloneSprite(t_fot_zombie->GetName());
	zombie->set_exist(true);
	zombie->SetSpritePosition(CSystem::GetScreenRight(), y_slot[y] - zombie->GetSpriteHeight() / 2);
	zombie->move();

	return zombie;
}

Plant* CGameMain::create_pea_shooter(float x, float y) {
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
	pshtr->SetSpriteImmovable(true);
	rect->SpriteMountToSprite(pshtr->GetName(), 11, -0.5);
	pshtr->set_exist(false);
	return pshtr;
}

Plant* CGameMain::create_sunflower(float x, float y) {
	Sun* sun = new Sun(CSystem::MakeSpriteName(t_sun->GetName(), vec_sun.size()), 25);
	vec_sun.push_back(sun);
	name_to_sprite[sun->GetName()] = sun;
	sun->set_exist(false);
	std::cout << sun->is_exist() << std::endl;

	Sunflower* sf = new Sunflower(CSystem::MakeSpriteName(t_sunflower->GetName(), vec_sunflower.size()), sun);
	vec_sunflower.push_back(sf);
	name_to_sprite[sf->GetName()] = sf;

	sf->CloneSprite(t_sunflower->GetName());
	sf->SetSpritePosition(x, y);
	sf->SetSpriteImmovable(true);
	sf->set_exist(false);
	return sf;
}

Plant* CGameMain::create_cherry_bomb(float x, float y, long double plant_time) {
	// 创建樱桃炸弹的 攻击范围
	//Range* rect = new Range(CSystem::MakeSpriteName(t_range->GetName(), vec_range.size()));
	//vec_range.push_back(rect);
	//name_to_sprite[rect->GetName()] = rect;
	//rect->CloneSprite(t_range->GetName());
	//rect->set_exist(true);
	//rect->SetSpriteWidth(26.610);
	//rect->SetSpriteHeight(22.156);

	// 创建樱桃炸弹的 爆炸
	Boom* boom = new Boom(CSystem::MakeSpriteName("Boom", vec_boom.size()));
	vec_boom.push_back(boom);
	name_to_sprite[boom->GetName()] = boom;
	boom->set_exist(false);

	CherryBomb* cb = new CherryBomb(CSystem::MakeSpriteName(t_cherry_bomb->GetName(), vec_cherry_bomb.size()), boom, plant_time);
	std::cout << cb->get_type();
	vec_cherry_bomb.push_back(cb);
	name_to_sprite[cb->GetName()] = cb;

	cb->CloneSprite(t_cherry_bomb->GetName());
	cb->SetSpritePosition(x, y);
	cb->SetSpriteImmovable(true);
	//rect->SpriteMountToSprite(cb->GetName(), 0, 0);
	cb->set_exist(false);
	return cb;
}

Plant* CGameMain::create_wall_nut(float x, float y) {

	WallNut* wn = new WallNut(CSystem::MakeSpriteName(t_wall_nut->GetName(), vec_wall_nut.size()));
	vec_wall_nut.push_back(wn);
	name_to_sprite[wn->GetName()] = wn;
	wn->CloneSprite(t_wall_nut->GetName());
	wn->SetSpritePosition(x, y);
	wn->SetSpriteImmovable(true);
	wn->set_exist(false);
	return wn;
}

Plant* CGameMain::create_potato_mine(float x, float y, long double plant_time) {
	std::cout << "Potato Mine" << std::endl;
	// 创建土豆地雷的 攻击范围
	Range* rect = new Range(CSystem::MakeSpriteName(t_range->GetName(), vec_range.size()));
	vec_range.push_back(rect);
	name_to_sprite[rect->GetName()] = rect;
	rect->CloneSprite(t_range->GetName());
	rect->set_exist(true);
	rect->SetSpriteWidth(16.375);
	rect->SetSpriteHeight(11.500);

	// 创建土豆地雷的 爆炸
	Boom* boom = new Boom(CSystem::MakeSpriteName("Boom", vec_boom.size()));
	vec_boom.push_back(boom);
	name_to_sprite[boom->GetName()] = boom;
	boom->set_exist(false);

	PotatoMine* pm = new PotatoMine(CSystem::MakeSpriteName(t_potato_mine->GetName(), vec_potato_mine.size()), boom, plant_time);
	std::cout << pm->get_type();
	vec_potato_mine.push_back(pm);
	name_to_sprite[pm->GetName()] = pm;

	pm->CloneSprite(t_potato_mine->GetName());
	pm->SetSpritePosition(x, y);
	pm->SetSpriteImmovable(true);
	
	rect->SpriteMountToSprite(pm->GetName(), 0, 0);
	pm->set_exist(false);
	return pm;
}

Plant* CGameMain::create_jalapeno(float x, float y, long double plant_time) {
	// 创建火爆辣椒的 攻击范围
	//Range* rect = new Range(CSystem::MakeSpriteName(t_range->GetName(), vec_range.size()));
	//vec_range.push_back(rect);
	//name_to_sprite[rect->GetName()] = rect;
	//rect->CloneSprite(t_range->GetName());
	//rect->set_exist(true);
	//rect->SetSpriteWidth(26.610);
	//rect->SetSpriteHeight(22.156);

	// 创建火爆辣椒的 爆炸
	Boom* boom = new Boom(CSystem::MakeSpriteName("Boom", vec_boom.size()));
	vec_boom.push_back(boom);
	name_to_sprite[boom->GetName()] = boom;
	boom->set_exist(false);

	Jalapeno* jp = new Jalapeno(CSystem::MakeSpriteName(t_jalapeno->GetName(), vec_jalapeno.size()), boom, plant_time);
	vec_jalapeno.push_back(jp);
	name_to_sprite[jp->GetName()] = jp;

	jp->CloneSprite(t_jalapeno->GetName());
	jp->SetSpritePosition(x, y);
	jp->SetSpriteImmovable(true);
	//rect->SpriteMountToSprite(jp->GetName(), 0, 0);
	jp->set_exist(false);
	return jp;
}



void CGameMain::create_gray_mask(Card* card) {
	CSprite* gray_mask;
	std::string name = std::string(card->GetName()) + "Mask";
	gray_mask = new CSprite(name.c_str(), "GrayMask");
	gray_mask->SetSpritePosition(card->GetSpritePositionX(), card->GetSpritePositionY());
	gray_mask->SpriteMountToSprite(card->GetName(), 0, 0);
	card->set_mask(gray_mask);
}

std::vector<PvZSprite*> CGameMain::get_sprites_by_position(float x, float y) {
	std::cout << "CLICK:" << x << " " << y << std::endl;
	std::vector<PvZSprite*> res;
	for (std::pair<std::string, PvZSprite*> sprite : name_to_sprite) {
		if (sprite.second->is_exist() && sprite.second->IsPointInSprite(x, y) && sprite.second->get_type() != "Range") {
			res.push_back(sprite.second);
		}
	}
	// 右值引用 可以提高效率
	return std::move(res);
}


bool CGameMain::planting(Plant* plant) {
	if (sun_count >= plant->get_cost()) {
		sun_count -= plant->get_cost();
		sun_num->SetTextValue(sun_count);
		return true;
	}
	return false;
}

void CGameMain::output_sun(int num) {
	Sun* sun = new Sun(CSystem::MakeSpriteName(t_sun->GetName(), vec_sun.size()), num);
	vec_sun.push_back(sun);
	name_to_sprite[sun->GetName()] = sun;
	sun->CloneSprite(t_sun->GetName());
	
	int pos_x = CSystem::RandomRange(CSystem::GetScreenLeft() + 5, CSystem::GetScreenRight() - 5);
	int pos_y = CSystem::RandomRange(CSystem::GetScreenTop() + 10, CSystem::GetScreenBottom() - 5);

	sun->SetSpritePosition(pos_x, CSystem::GetScreenTop() + 10);
	sun->SpriteMoveTo(pos_x, pos_y, 15, true);

	sun->set_exist(true);
	sun->SetSpriteLifeTime(10);
}

void CGameMain::add_sun(int num) {
	sun_count += num;
	sun_num->SetTextValue(sun_count);
}

