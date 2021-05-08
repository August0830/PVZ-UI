#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <Windows.h>
#include <map>
#define WH_KEYBOARD_LL 13
const int unit_max = 6;//һ�������ܹ����ɵ������������
//#include "Zombie.h"
//#include "Plant.h"
const int X_INTERVAL = 15;
const int  Y_INTERVAL = 7;
extern int shooter_attack_val;
extern int shooter_life_val;
extern int shooter_sun_price_val;
extern int bullet_fly_speed;
extern int double_shooter_sun_price_val;
extern int turn;
extern int defense_life_val;
extern int defense_sun_price_val;
extern int bomb_sun_price_val;
extern int z_normal_att;
extern int z_normal_life;
extern int z_normal_speed;
using namespace std;
class Zombie;
class Plant;
class Bullet;
class GardenBoard
{
	friend class Plant;
	friend class Zombie;
	friend class Shooter;
	friend class Bullet;
	//��԰�е��������ж��󽻻��Ĺ��ܣ���ҪƵ���������ǵ����ݣ�������ó���Ԫ��������߳�������Ч��
private:
	int row_total;//3 0~2
	int col_total;//8 0~7
	int sun_deposit;//ӵ�е�̫���� ��ʱ����
	int point_cnt;//�Ʒ� 
	vector<int> zombie_cnt;//���н�ʬ����  ����ÿһ������¼
	int zombie_max;//�޶���ʬ���� ���Ը�����Ϸ���Ѷ�������
	int sunflower_cnt;//���տ�����ͳ�ƣ���������������֮������
public:
	//int sunflower_cnt;
	//int sun_deposit;
	HANDLE hOutput;
	HANDLE hIn;
	vector<vector<void*>> garden_pos;
	vector<vector<int>> garden_pos_cnt;
	GardenBoard(int row_total, int col_total,HANDLE hIn,HANDLE hOutput) :point_cnt(0), sun_deposit(50),zombie_max(4),
		sunflower_cnt(0)
	{
		for (int i = 0; i < row_total; ++i)
		{
			vector<void*> tmp(col_total);
			garden_pos.push_back(tmp);
			vector<int> ini(col_total, 0);
			garden_pos_cnt.push_back(ini);
		}//�˴�������NULLָ��
		zombie_cnt.resize(row_total, 0);
		this->row_total = row_total;
		this->col_total = col_total;
		this->hIn = hIn;
		this->hOutput = hOutput;
	};
	void print_garden();//��ӡ��� 
	void SetPos(HANDLE HOutput,int x, int y);
	bool ClearConsole(HANDLE hOut);//refresh
	void refresh_state(HANDLE& hOutput, HANDLE& hIn, DWORD start);//ˢ��λ�� ��ֲ��ͽ�ʬ���๥�� λ���ж��ڻ�԰�����
	//������ȥ��ֲ��ͽ�ʬ���ҶԽ�ʬ�Ʒ�
	void generate_sun();//refreshʱ����̫������һ��ʼ��һ����Ŀ���� �������տ��������տ���������
	void get_score(int score) { point_cnt += score; }//���¼Ƿ���
	void zombie_counting(int cnt,int row){ zombie_cnt[row] += cnt; }//ͳ�����н�ʬ��
	bool random_generate_zom();//���ɽ�ʬ ���Ը����ܵĽ�ʬ����ÿ�еĽ�ʬ������
	void open_shop(HANDLE& hIn);//�ڲ�����Ӧ����֮�� ����ֲ�� �����λ����row/col_total����һ�� �Ǹ���������˼
};


class Plant
{
	friend class GardenBoard;
public:
	int row;
	int col;//λ����Ϣ
	int life;//����ֵ
	int sun_price;//��������������
	char type;//����԰����ֲ��ͽ�ʬ
	string plant_name;//ϸ�ֲ�ͬ��ֲ�����
	string func_type;
	//�������ͣ�����������(Shooter)��ը����(Bomb) ������(Defense) Ч����(Efficient)��
	Plant() :row(0), col(0), life(30), sun_price(0), type('p'), plant_name("plant"),func_type("plant") {};
	int get_col()const { return col; }//��������ʱ��ȡ������
	void get_hurt(Zombie* zombie);//����ʬ����
	int price()const { return sun_price; }//��������ʱ��ȡ����ֲ������������
};
class Sunflower :public Plant
{
	friend class GardenBoard;
public:
	Sunflower(int r, int c) {
		row = r; col = c; plant_name = "Sunflower";
		func_type = "Efficient";
		sun_price = 10;
		life = 20;
	}

};
class Shooter :public Plant//
{
	friend class GardenBoard;
	friend class Bullet;
	friend class Frozen_Bullet;
private:
	int attack;
	vector<Bullet*> bullet_set;//��ʱpublic ֮���garden����
public:
	Shooter():attack(shooter_attack_val){};
	Shooter(int r, int c) :attack(shooter_attack_val)
	{
		row = r;
		col = c;
		life = shooter_life_val;
		sun_price = shooter_sun_price_val;
		plant_name = "Shooter";
		func_type = "Shooter";
		bullet_set.clear();
	}
	void attacking();//ͨ�������ӵ�������
	int get_row()const { return row; }
	int get_col()const { return col; }	
};
class Double_Shooter :public Shooter
{
	friend class GardenBoard;
	friend class Bullet;
private:
	int attack;
	vector<Bullet*> bullet_set;
public:
	Double_Shooter(int r, int c) :attack(shooter_attack_val)
	{
		row = r;
		col = c;
		life = shooter_life_val;
		sun_price = double_shooter_sun_price_val;
		plant_name = "Double Shooter";
		func_type = "Shooter";
		bullet_set.clear();
	}
	void attacking();
};
class Bullet
{
	friend class Shooter;
	friend class GardenBoard;
private: 
	int row;
	int col;
	int attack;//�ӵ��Ĺ���ֵ��ֲ����֣�����
	int fly_speed;//ÿ�غ��ƶ��ĸ�����
public:
	Bullet() :row(0), col(0), attack(9),fly_speed(bullet_fly_speed) {};
	Bullet(Shooter* shot,int fly) 
	{ 
		row = shot->row; 
		col = shot->col; 
		attack = shot->attack;
		fly_speed= fly;
	}
	void move(vector<vector<void*>>& garden_pos);//�ӵ��Լ�����λ��
	void print_bullet(HANDLE hOutput, int duplicated);//�ӵ����д�ӡλ��
	virtual void attacking(Zombie* zombie);//�ӵ�������ʬ
	int get_col()const { return col; }//��������
};
class Frozen_Shooter:public Shooter
{
	friend class GardenBoard;
	friend class Bullet;
private:
	int attack;
	vector<Bullet*> bullet_set;
public:
	Frozen_Shooter(int r, int c) :attack(shooter_attack_val)
	{
		row = r;
		col = c;
		life = shooter_life_val;
		sun_price = double_shooter_sun_price_val;
		plant_name = "Frozen Shooter";
		func_type = "Shooter";
		bullet_set.clear();
	}
};
class Nut :public Plant
{
	friend class GardenBoard;
	friend class Bullet;
	friend class Frozen_Bullet;
public:
	Nut() {};
	Nut(int r, int c)
	{
		row = r;
		col = c;
		life = shooter_life_val+15;
		sun_price = defense_sun_price_val;
		plant_name = "Nut";
		func_type = "Defense";
	}
};
class High_Nut :public Nut
{
	friend class GardenBoard;
	friend class Bullet;
	friend class Frozen_Bullet;
public:
	High_Nut(int r, int c)
	{
		row = r;
		col = c;
		life = shooter_life_val*2;
		sun_price = defense_sun_price_val+10;
		plant_name = "High Nut";
		func_type = "Defense";
	}
};

class Squash :public Plant
{
	friend class GardenBoard;
public:
	Squash()  {};
	Squash(int r, int c)
	{
		row = r;
		col = c;
		life = shooter_life_val;
		sun_price = shooter_sun_price_val;
		plant_name = "Squash";
		func_type = "Bomb";
	}
	void attacking(vector<vector<void*>>& garden_pos);
};

class Cherry_Bomb :public Plant
{
	friend class GardenBoard;
public:
	Cherry_Bomb() {};
	Cherry_Bomb(int r, int c)
	{
		row = r;
		col = c;
		life = shooter_life_val;
		sun_price = bomb_sun_price_val + 10;
		plant_name = "Cherry Bomb";
		func_type = "Bomb";
	}
	void attacking(vector<vector<void*>>& garden_pos);
};

class Zombie
{
	friend class GardenBoard;
	friend class Frozen_Bullet;
//private:	
	//�ж��ֽ�ʬ֮��������	
public:
	int life;//����ֵ
	int row;
	int col;
	char type;
	string zombie_name;
	int attack;//������
	int speed;//�ƶ��ٶ� ��Ϊ���ٻغ��ƶ�һ��
	Zombie() :row(0), col(0), type('z'), life(z_normal_life), speed(z_normal_speed), attack(z_normal_att),zombie_name("Z") {};
	Zombie(int r, int c) :life(25), attack(z_normal_att), speed(1), type('z'), zombie_name("Z")
	{
		row = r; col = c;
	}
	Zombie(int r, int c, int _life, int _att, int _speed) :type('z'), zombie_name("Z")
	{
		life = _life; attack = _att; speed = _speed; row = r; col = c;
	}
	void get_hurted(int attack_value);//����֮�������������й����Ե�ֲ�� ����ֻ���빥��ֵ
	bool move(vector<vector<int>>& garden_pos_cnt, int x0, int y0);//�����ƶ�
	virtual int attacking()const
	{
		return attack;
	}//��ȡ����ֵ
	int get_row()const { return row; }
	int get_col()const { return col; }//��ȡλ��
	void reset_speed(int new_val) { speed = new_val; }
	virtual void print_Z() { cout << zombie_name <<" "<< life; };
};
class Zombie_Normal :public Zombie
{
public:
	Zombie_Normal(int r, int c)
	{
		row = r;
		col = c;
		zombie_name = "Zombie";
		attack = z_normal_life;
	}
	void print_Z() { cout << zombie_name << " " << life; }
};
class Conhead_Zombie:public Zombie
{
public:
	Conhead_Zombie(int r, int c)
	{
		row = r;
		col = c;
		life = z_normal_life + 15;
		zombie_name = "Conhead Zombie";
		attack = 5;
	}
	void print_Z() { cout << zombie_name << " " << life; }
};
class Paper_Zombie :public Zombie
{
public:
	Paper_Zombie(int r, int c)
	{
		row = r;
		col = c;
		life = z_normal_life + 15;
		zombie_name = "Paper Zombie";
	}
	void print_Z();
	void change_state();
};
class Jester_Zombie :public Zombie
{
public:
	Jester_Zombie(int r, int c)
	{
		row = r;
		col = c;
		life = z_normal_life*4;
		zombie_name = "Jester Zombie";
	}
	void print_Z() { cout << zombie_name << " " << life; };
	void self_attacking(vector<vector<void*>>& garden_pos);
};
class Pole_Zombie :public Zombie
{
public:
	int pole;
	Pole_Zombie(int r, int c)
	{
		row = r;
		col = c;
		life = z_normal_life * 2;
		zombie_name = "Pole Zombie";
		pole = 1;
	}
	void print_Z() { cout << zombie_name << " " << life; }
	void jump(vector<vector<int>>& garden_pos_cnt);
};
class Stone_Zombie :public Zombie
{
public:
	int stone;
	Stone_Zombie(int r, int c)
	{
		row = r;
		col = c;
		life = z_normal_life * 3;
		zombie_name = "Stone Zombie";
		stone = 2;
	}
	void print_Z() { cout << zombie_name << " " << life; }
	int attacking();
};