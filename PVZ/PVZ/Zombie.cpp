#include <iostream>
#include "GardenBoard.h"
extern bool GAME_FAIL;
using namespace std;
int z_normal_att = 5;
int z_normal_life = 25;
void Zombie::get_hurted(int attack_value)
{
	life -= attack_value;
	//cout << "zombie life " << life<<endl;
}
bool Zombie::move(vector<vector<int>>& garden_pos_cnt, int x0, int y0)
{
    //cout << " sin "<< speed;
    if (turn % speed == 0)
    {
        int newy = y0 - 1;
        if (garden_pos_cnt[x0][newy] < unit_max)//�����Ѿ����˵ĵؿ鱻����
        {
            garden_pos_cnt[x0][y0]--;
            garden_pos_cnt[x0][newy]++;
            this->col = newy;
            //swap(garden_pos_cnt[x0][newy], garden_pos[x0][y0]);
            //��԰����Ϣ�ͽ�ʬ����Ϣͬʱά��
            //garden_pos[x0][y0] = NULL;
        }
        if (newy <= 0)
            GAME_FAIL = true;
    }
    
    return true;
}