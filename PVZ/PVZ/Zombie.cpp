#include <iostream>
#include "GardenBoard.h"
extern bool GAME_FAIL;
using namespace std;
void Zombie::get_hurted(int attack_value)
{
	life -= attack_value;
	//cout << "zombie life " << life<<endl;
}
bool Zombie::move(vector<vector<void*>>& garden_pos, int x0, int y0)
{
    int newy = y0 - speed;
    if (garden_pos[x0][newy] == NULL)//ֻ���߿յĵؿ� �����ǿյؿ鱻����
    {
        this->col = newy;
        swap(garden_pos[x0][newy], garden_pos[x0][y0]);
        //��԰����Ϣ�ͽ�ʬ����Ϣͬʱά��
        //garden_pos[x0][y0] = NULL;
    }
    if (newy <= 0)
        GAME_FAIL = true;
    return true;
}