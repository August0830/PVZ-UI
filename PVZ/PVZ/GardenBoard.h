#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <Windows.h>
#define WH_KEYBOARD_LL 13

//#include "Zombie.h"
//#include "Plant.h"
const int X_INTERVAL = 15;
const int  Y_INTERVAL = 7;
extern int shooter_attack_val;
extern int shooter_life_val;
extern int shooter_sun_price_val;
extern int bullet_fly_speed;
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
	GardenBoard(int row_total, int col_total,HANDLE hIn,HANDLE hOutput) :point_cnt(0), sun_deposit(100),zombie_max(4),
		sunflower_cnt(0)
	{
		for (int i = 0; i < row_total; ++i)
		{
			vector<void*> tmp(col_total);
			garden_pos.push_back(tmp);
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
	Plant() :row(0), col(0), life(30), sun_price(0), type('p'), plant_name("plant") {};
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
		sun_price = 10;
		life = 20;
	}

};
class Shooter :public Plant//
{
	friend class GardenBoard;
	friend class Bullet;
private:
	int attack;
	vector<Bullet*> bullet_set;//��ʱpublic ֮���garden����
public:
	Shooter(int r, int c) :attack(shooter_attack_val)
	{
		row = r;
		col = c;
		life = shooter_life_val;
		sun_price = shooter_sun_price_val;
		plant_name = "Shooter";
		bullet_set.clear();
	}
	void attacking();//ͨ�������ӵ�������
	int get_row()const { return row; }
	int get_col()const { return col; }	
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
	void print_bullet(HANDLE hOutput);//�ӵ����д�ӡλ��
	void attacking(Zombie* zombie);//�ӵ�������ʬ
	int get_col()const { return col; }//��������
};

class Zombie
{
	friend class GardenBoard;
private:
	int life;//����ֵ
	int attack;//������
	int speed;//�ƶ��ٶ� ͬ����һ�غ��ƶ��ĸ���
	//�ж��ֽ�ʬ֮��������

public:
	int row;
	int col;
	char type;
	Zombie(int r, int c) :life(25), attack(5), speed(1), type('z')
	{
		row = r; col = c;
	}
	Zombie(int r, int c, int _life, int _att, int _speed) :type('z')
	{
		life = _life; attack = _att; speed = _speed; row = r; col = c;
	}
	void get_hurted(int attack_value);//����֮�������������й����Ե�ֲ�� ����ֻ���빥��ֵ
	bool move(vector<vector<void*>>& garden_pos, int x0, int y0);//�����ƶ�
	int attacking()const
	{
		return attack;
	}//��ȡ����ֵ
	int get_row()const { return row; }
	int get_col()const { return col; }//��ȡλ��
};