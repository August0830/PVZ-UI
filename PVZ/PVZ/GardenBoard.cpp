#include <iostream>
#include "GardenBoard.h"
#include <stdio.h>  
#include <windows.h>  
#include <conio.h>  
#include <time.h>
using namespace std;
bool GAME_FAIL = false;//����ȫ�ֱ����Ǳ���ͨ�ţ���ʱ�����л����
extern const int Y_MAX;
int turn = 0;
void GardenBoard::generate_sun()
{
    sun_deposit += 10+10*sunflower_cnt;
}
void GardenBoard::SetPos(HANDLE HOutput,int x, int y)
{
    COORD point = { x, y };//���Ҫ���õ�λ��x,y
    //HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//ʹ��GetStdHandle(STD_OUTPUT_HANDLE)����ȡ��׼����ľ��
    SetConsoleCursorPosition(HOutput, point);//���ù��λ��
}
void GardenBoard::print_garden()
{
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hOutput, &bInfo);
    COORD tst = { 0,0 };
    for (tst.X = 15; tst.X <= 115; tst.X += X_INTERVAL)
    {
        tst.Y = 0;
        do {
            SetConsoleCursorPosition(hOutput, tst);
            cout << "#";
            tst.Y++;
        } while (tst.Y <= 21);
    }
    tst.X = 0; tst.Y = 29;
    do {
        SetConsoleCursorPosition(hOutput, tst);
        cout << "#";
        tst.X++;
    } while (tst.X <= 119);
    for (tst.Y = 7; tst.Y <= 21; tst.Y += Y_INTERVAL)
    {
        tst.X = 0;
        do {
            SetConsoleCursorPosition(hOutput, tst);
            cout << "#";
            tst.X++;
        } while (tst.X <= 119);
    }//��԰�Ļ���  ����װ����ǿ��ǵ�ʹ��Ƶ�����ҵ��ľ��û�м�ʱ�ͷ�
    /*for (tst.X = 7; tst.X < 119; tst.X += X_INTERVAL)
    {
        for (tst.Y = 3; tst.Y < 22; tst.Y += Y_INTERVAL)
        {
            SetConsoleCursorPosition(hOutput, tst);
            cout << "#";
        }
    }//ÿ�����ӵ�����λ�� ѡ��ʱ��λ�����ó�����λ�� ��ȡÿһ��pos�еĸ������Զ�ת����ָ��λ��*/
    map<pair<int, int>, int> adjust_pos;
    for (int i = 0; i < row_total; ++i)
    {
        //tst.Y = 3 + 7 * i;
        //tst.Y = 1+7 * i;
        for (auto plant : garden_pos[i])
        {
            if (!plant || ((Plant*)plant)->type != 'p') continue;
            if (adjust_pos.count(make_pair(i, ((Plant*)plant)->col)) == 0)
                adjust_pos[make_pair(i, ((Plant*)plant)->col)] = 1;
            else
                adjust_pos[make_pair(i, ((Plant*)plant)->col)]++;
            tst.X = 4 + 15 * ((Plant*)plant)->col;
            //tst.Y++;
            tst.Y = 7 * i + adjust_pos[make_pair(i, ((Plant*)plant)->col)];
            SetConsoleCursorPosition(hOutput, tst);
            cout << ((Plant*)plant)->plant_name<<" "<< ((Plant*)plant)->life;
        }
        for (auto zombie : garden_pos[i])
        {
            if (!zombie || ((Zombie*)zombie)->type != 'z') continue;
            if (adjust_pos.count(make_pair(i, (((Zombie*)zombie)->col) == 0)))
                adjust_pos[make_pair(i, ((Zombie*)zombie)->col)] = 1;
            else
                adjust_pos[make_pair(i, ((Zombie*)zombie)->col)]++;
            tst.X = 7 + 15 * ((Zombie*)zombie)->col;
            tst.Y = 7 * i + adjust_pos[make_pair(i, ((Zombie*)zombie)->col)];
            //tst.Y--;
            SetConsoleCursorPosition(hOutput, tst);
            cout << "Zombie "<<((Zombie*)zombie)->life;// << " " << ((Zombie*)zombie)->col << " " << ;
        }
    }

    tst.X = 0; tst.Y = 22;
    SetConsoleCursorPosition(hOutput, tst);
    cout << "Total Points: " << point_cnt<< " Turn: "<<turn;
    tst.X = 0; tst.Y = 23;
    SetConsoleCursorPosition(hOutput, tst);
    cout << "Sun Deposit: " << sun_deposit;
    tst.X = 30; tst.Y = 22;
    SetConsoleCursorPosition(hOutput, tst);
    cout << "Shop: ";//
    cout << "a.Sunflower 10 ";
    cout << " b.Pea Shooter " << shooter_sun_price_val;
    cout<<" c.Double Shooter "<< double_shooter_sun_price_val;
    cout<<" d.Frozen Shooter "<< double_shooter_sun_price_val;
    cout << " e.Nut " << defense_sun_price_val;
    tst.X = 30; tst.Y = 23;
    SetConsoleCursorPosition(hOutput, tst);
    cout << "f.High Nut " << defense_sun_price_val + 10;
    cout << " g.Squash " << bomb_sun_price_val;
    cout << " h.Cherry Bomb " << bomb_sun_price_val + 10;
    tst.X = 0; tst.Y = 29;
    SetConsoleCursorPosition(hOutput, tst);//���������ʾ
    //CloseHandle(hOutput);
}
bool GardenBoard::ClearConsole(HANDLE hOut) {
    CONSOLE_SCREEN_BUFFER_INFO cinfo;//���ڴ������̨��������Ϣ,��������Ҫ��ȡ����̨��������С
    DWORD recnum;
    GetConsoleScreenBufferInfo(hOut, &cinfo);
    //cinfo.dwSize������ǻ�������С
    //cinfo.dwSize.X * cinfo.dwSize.Y ���������ַ���
    COORD zero = { 0,0 };
    FillConsoleOutputCharacterW(hOut, L' ', cinfo.dwSize.X * cinfo.dwSize.Y, zero, &recnum);//��{0,0}����ʼ���' '�ַ�,�ɹ�������Ϊrecnum
    FillConsoleOutputAttribute(hOut, 0, cinfo.dwSize.X * cinfo.dwSize.Y, zero, &recnum);//���������ɫ,������ǵ�һ��ɫ,���ܻ�������ַ�������ɫû�����������
    SetConsoleCursorPosition(hOut, zero);//�������Ϊ{0,0}
    if (recnum != cinfo.dwSize.X * cinfo.dwSize.Y) return FALSE;
    return TRUE;
}
bool GardenBoard::random_generate_zom()
{
    int sum = 0;
    for (auto num : zombie_cnt)
    {
        //cout << num << " ";
        sum += num;
    }
    if (sum >= zombie_max)
        return false;
    srand((unsigned int)(time(NULL)));
    int row_ini = rand() % row_total;
    for (int i = 0; i < 2*row_total&& garden_pos_cnt[row_ini][col_total - 1]<unit_max;
        ++i)
        //����һ�м���̫�ཀྵʬ
    {
            row_ini = rand() % row_total;
    }
    if (garden_pos_cnt[row_ini][col_total - 1]==unit_max)
        return false;
    else
    {
        //cout << row_ini << endl;
        Zombie* zm = new Zombie(row_ini,col_total-1);  
        //garden_pos[zm->row][zm->col] = zm;
        garden_pos[zm->row].push_back(zm);
        garden_pos_cnt[zm->row][zm->col]++;
        zombie_cnt[zm->row]++;
        int val = rand() % 3;
        //cout << val << " v";
        if (val == 0)
        {
            Zombie* zm_more = new Zombie(row_ini, col_total - 1);
            garden_pos[zm_more->row].push_back(zm_more);
            garden_pos_cnt[zm_more->row][zm_more->col]++;
            zombie_cnt[zm_more->row]++;
        }//�����һ���ؿ����������ʬ
        //cout << "generate zombie\n";
    }
}
void GardenBoard::refresh_state(HANDLE& hOutput, HANDLE& hIn, DWORD start)
{
    DWORD res;
    INPUT_RECORD Rec;
    
    while (1)//��Ϸ��ѭ��
    {
        generate_sun();
        ClearConsole(hOutput);
        if (GAME_FAIL)
        {
            ClearConsole(hOutput);
            //adjust format
            cout << "Game Failed!Zombies win!\n";
            break;
        }//��״̬���²���ʾ��ɺ��ж��Ƿ����
        random_generate_zom();
        turn++;
        print_garden();
        for (int i = 0; i < row_total; ++i)
        {
            //for (int j = 0; j < col_total; ++j)
            for(auto ptr:garden_pos[i])
            {
                
                //if (!garden_pos[i][j]) continue;
                if (!ptr) continue;
                Plant* plt = (Plant*)ptr;//(garden_pos[i][j]);
                Zombie* zom = (Zombie*)ptr;//(garden_pos[i][j]);
                if (plt->type == 'p' && plt->func_type == "Shooter")
                {
                    Shooter* shot = (Shooter*)plt;
                    //for (int k = j + 1; k < col_total; ++k)
                    for (auto nptr : garden_pos[i])
                    {
                        //�����м�⵽��ʬ�ҽ�ʬ��ֲ���Ҳ�ͷ����ӵ�
                        //if (garden_pos[i][k] && ((Zombie*)(garden_pos[i][k]))->type == 'z')
                        if (nptr != ptr && nptr != NULL)
                        {
                            if (((Zombie*)nptr)->type != 'z' || ((Zombie*)nptr)->col < shot->col) 
                                continue;
                            //((Shooter*)plt)->attacking((Zombie*)(garden.garden_pos[i][k]));                                                   
                            shot->attacking();
                            //�ӵ�
                            for (vector<Bullet*>::iterator it = shot->bullet_set.begin(); it != shot->bullet_set.end();)
                            {
                                if ((*it)->col > Y_MAX)
                                {
                                    it = shot->bullet_set.erase(it);
                                }//����ɳ�������ӵ�
                                else if ((*it)->col - 1 == ((Zombie*)nptr)->col
                                    || (*it)->col == ((Zombie*)nptr)->col)
                                    //(garden_pos[i][k])
                                {
                                    (*it)->attacking((Zombie*)nptr);
                                    if (shot->plant_name == "Frozen Shooter")
                                        ((Zombie*)nptr)->reset_speed(10);
                                    // output = { 31,24 };
                                    //SetConsoleCursorPosition(hOutput, output);
                                    //cout << "Shooter attacked! ";
                                    it = shot->bullet_set.erase(it);
                                }//�ӵ��뽩ʬ��ͬһ��������һʱ�̽�ʬ���ӵ���������ʱ�ӵ���������
                                else
                                {
                                    it++;
                                }//������ɾ���ķ���
                            }
                        }
                    }
                }
                if (plt->type == 'p' && plt->func_type == "Bomb")
                {
                    if (plt->plant_name == "Squash")
                        ((Squash*)plt)->attacking(this->garden_pos);
                    else if (plt->plant_name == "Cherry Bomb")
                        ((Cherry_Bomb*)plt)->attacking(this->garden_pos);
                }
                if (zom->type == 'z')
                {
                    if (garden_pos_cnt[zom->row][zom->col]!=0)
                        //(garden_pos[zom->row][zom->col - 1])
                    {
                        for (auto ptr : garden_pos[zom->row])
                        {
                            if (!ptr)
                                continue;
                            Plant* plt = (Plant*)ptr;
                                //(Plant*)(garden_pos[zom->row][zom->col - 1]);
                            //if (plt->type == 'p')
                            if( plt->type == 'p' && plt->col == zom->col - 1)
                            {
                                plt->get_hurt(zom);
                                // COORD output = { 32,24 };
                                 //SetConsoleCursorPosition(hOutput, output);
                                 //cout << "Zombie attacked! ";
                            }
                        }
                        
                    }
                }
            }
        }//ֲ��ͽ�ʬ���๥�������ڻ�԰�ṩ��λ����Ϣ�����ù����ĺ���

        //ֲ��ͽ�ʬ��״̬����
        
        for (int i = 0; i < row_total; ++i)
        {
            map<pair<int, int>, int> bullet_adjust;
            for (vector<void*>::iterator it = garden_pos[i].begin(); it != garden_pos[i].end();)
            {
                if ((*it) != NULL && ((Plant*)(*it))->type == 'p')//ֲ�����
                {
                    if (((Plant*)(*it))->life <= 0)
                        it = garden_pos[i].erase(it);//���������ֲ��
                    else if (((Shooter*)(*it))->func_type == "Shooter")//�����ӵ�λ��
                    {
                        Shooter* shot = ((Shooter*)(*it));
                        for (vector<Bullet*>::iterator iter = shot->bullet_set.begin(); iter != shot->bullet_set.end();)
                        {
                            if ((*iter)->col >= Y_MAX)
                            {
                                iter = shot->bullet_set.erase(iter);
                            }//����Ѿ��ɳ�������ӵ�
                            else
                            {
                                if (bullet_adjust.count(make_pair((*iter)->row, (*iter)->col)) == 0)
                                    bullet_adjust[make_pair((*iter)->row, (*iter)->col)] = 1;
                                else
                                    bullet_adjust[make_pair((*iter)->row, (*iter)->col)]++;
                                (*iter)->move(garden_pos);
                                (*iter)->print_bullet(hOutput, bullet_adjust[make_pair((*iter)->row, (*iter)->col)]);
                                iter++;
                            }//�Զ��ƶ����Ҵ�ӡ
                        }
                        it++;
                    }
                    else
                        it++;
                }
                else if ((*it) != NULL && ((Zombie*)(*it))->type == 'z')//��ʬ����
                {
                    if (((Zombie*)(*it))->life <= 0)
                    {
                        get_score(10);//֮��������óɲ�ͬ�ķ���ֵ
                        zombie_counting(-1, i);
                        COORD output = { 7 + 15 * ((Zombie*)(*it))->col,3 + 7 * i };
                        if (output.X <= 119)
                        {
                            SetConsoleCursorPosition(hOutput, output);
                            cout << "Zombie died!";
                        }
                        it = garden_pos[i].erase(it);//��������Ľ�ʬ
                        
                    }//��������Ľ�ʬ���ҼƷ�/���½�ʬ�� 
                    else
                    {
                        bool blocked = false;
                        for (auto ptr : garden_pos[i])
                        {
                            if (ptr != NULL && ptr!= (*it))
                            {
                                if (((Plant*)ptr)->col == ((Zombie*)(*it))->col - 1 && ((Plant*)ptr)->type == 'p')
                                {
                                    blocked = true;
                                    break;
                                }
                            }
                        }
                        if(!blocked)
                            ((Zombie*)(*it))->move(garden_pos_cnt, i, ((Zombie*)(*it))->col);
                        it++;
                    }//��ʬ�ƶ�
                }
                else 
                {
                    it++;
                }
              
            }
        }
        ReadConsoleInput(hIn, &Rec, 1, &res);
        if (Rec.EventType == KEY_EVENT && Rec.Event.KeyEvent.bKeyDown&&
            Rec.Event.KeyEvent.uChar.AsciiChar == 'b' || Rec.Event.KeyEvent.uChar.AsciiChar == 'B')
        {
            open_shop(hIn);
        }
        while (GetTickCount() - start < 1000);
        start = GetTickCount();//ҳ����ͣ
        SetConsoleCursorPosition(hOutput, COORD{ 30,26 });
    }
}
void GardenBoard::open_shop(HANDLE& hIn)
{
    DWORD res;
    INPUT_RECORD Rec;
    while (1)
    {
        ReadConsoleInput(hIn, &Rec, 1, &res);//��ȡһ���������
        if (Rec.EventType == KEY_EVENT && Rec.Event.KeyEvent.bKeyDown)
        {
            if (Rec.Event.KeyEvent.uChar.AsciiChar == 'b' || Rec.Event.KeyEvent.uChar.AsciiChar == 'B')
            {
                COORD display = { 30,25 };
                SetConsoleCursorPosition(hOutput, display);
                cout << "open shop\nUse keyboard to choose one:";
                //display.Y++;
                //SetConsoleCursorPosition(hOutput,display);
                char choice = 0;
                vector<char> shop_list{ 'a','b','c','d' ,'e','f','g','h'};
                while (1)
                {
                    ReadConsoleInput(hIn, &Rec, 1, &res);
                    if (Rec.EventType == KEY_EVENT && Rec.Event.KeyEvent.bKeyDown)
                    {
                        choice = Rec.Event.KeyEvent.uChar.AsciiChar;
                        cout << "choice: " << choice << endl;
                        if (choice == 'x' || find(shop_list.begin(), shop_list.end(), choice) != shop_list.end())
                            break;
                    }
                }
                //display.Y++;
                //SetConsoleCursorPosition(hOutput, display);
                if (choice == 'x')
                {
                    cout << "Cancel buying\n";
                    break;
                }
                cout << "Choose block\n";
                while (1)
                {
                    ReadConsoleInput(hIn, &Rec, 1, &res);
                    if (Rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//�����������
                    {
                        int row = Rec.Event.MouseEvent.dwMousePosition.Y / 7;
                        int col = Rec.Event.MouseEvent.dwMousePosition.X / 15;
                        cout << "row " << row << " ";
                        cout << "col " << col << endl;

                        while (1)
                        {
                            ReadConsoleInput(hIn, &Rec, 1, &res);
                            if ((Rec.EventType == KEY_EVENT && Rec.Event.KeyEvent.bKeyDown)
                                || (Rec.EventType == MOUSE_EVENT && Rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
                                break;
                        }
                        if (Rec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
                        {
                            cout << "Copy that!\n";
                            switch (choice)
                            {
                            case 'a':
                            {

                                Sunflower* sunflower = new Sunflower(row, col);
                                if (sun_deposit > sunflower->sun_price)
                                {
                                    //garden_pos[row][col] = sunflower;
                                    garden_pos[row].push_back(sunflower);
                                    garden_pos_cnt[row][col]++;
                                    cout << "Sunflower!\n";
                                    sunflower_cnt++;
                                    sun_deposit -= sunflower->sun_price;
                                }
                                else
                                {
                                    cout << "You are so poor!\n";
                                    delete sunflower;
                                }
                                break;
                            }
                            case 'b':
                            {
                                Shooter* shot = new Shooter(row, col);
                                if (sun_deposit > shot->sun_price)
                                {
                                    //garden_pos[row][col] = shot;
                                    garden_pos[row].push_back(shot);
                                    garden_pos_cnt[row][col]++;
                                    cout << "Pea Shooter!\n";
                                    sun_deposit -= shot->sun_price;
                                }
                                else
                                {
                                    cout << "You are so poor!\n";
                                    delete shot;
                                }
                                break;
                            }
                            case 'c':
                            {
                                Double_Shooter* dshot = new Double_Shooter(row,col);
                                if (sun_deposit > dshot->sun_price)
                                {
                                    //garden_pos[row][col] = shot;
                                    garden_pos[row].push_back(dshot);
                                    garden_pos_cnt[row][col]++;
                                    cout << "Double Shooter!\n";
                                    sun_deposit -= dshot->sun_price;
                                }
                                else
                                {
                                    cout << "You are so poor!\n";
                                    delete dshot;
                                }
                                break;
                            }
                            case 'd':
                            {
                                Frozen_Shooter* dshot = new Frozen_Shooter(row, col);
                                if (sun_deposit > dshot->sun_price)
                                {
                                    //garden_pos[row][col] = shot;
                                    garden_pos[row].push_back(dshot);
                                    garden_pos_cnt[row][col]++;
                                    cout << "Frozen Shooter!\n";
                                    sun_deposit -= dshot->sun_price;
                                }
                                else
                                {
                                    cout << "You are so poor!\n";
                                    delete dshot;
                                }
                                break;
                            }
                            case 'e':
                            {
                                Nut* nt = new Nut(row, col);
                                if (sun_deposit > nt->sun_price)
                                {
                                    //garden_pos[row][col] = shot;
                                    garden_pos[row].push_back(nt);
                                    garden_pos_cnt[row][col]++;
                                    cout << "Nut!\n";
                                    sun_deposit -= nt->sun_price;
                                }
                                else
                                {
                                    cout << "You are so poor!\n";
                                    delete nt;
                                }
                                break;
                            }
                            case 'f':
                            {
                                High_Nut* nt = new High_Nut(row, col);
                                if (sun_deposit > nt->sun_price)
                                {
                                    //garden_pos[row][col] = shot;
                                    garden_pos[row].push_back(nt);
                                    garden_pos_cnt[row][col]++;
                                    cout << "High Nut!\n";
                                    sun_deposit -= nt->sun_price;
                                }
                                else
                                {
                                    cout << "You are so poor!\n";
                                    delete nt;
                                }
                                break;
                            }
                            case 'g':
                            {
                                Squash* nt = new Squash(row, col);
                                if (sun_deposit > nt->sun_price)
                                {
                                    //garden_pos[row][col] = shot;
                                    garden_pos[row].push_back(nt);
                                    garden_pos_cnt[row][col]++;
                                    cout << "Squash!\n";
                                    sun_deposit -= nt->sun_price;
                                }
                                else
                                {
                                    cout << "You are so poor!\n";
                                    delete nt;
                                }
                                break;
                            }
                            case 'h':
                            {
                                Cherry_Bomb* nt = new Cherry_Bomb(row, col);
                                if (sun_deposit > nt->sun_price)
                                {
                                    //garden_pos[row][col] = shot;
                                    garden_pos[row].push_back(nt);
                                    garden_pos_cnt[row][col]++;
                                    cout << "Cherry Bomb!\n";
                                    sun_deposit -= nt->sun_price;
                                }
                                else
                                {
                                    cout << "You are so poor!\n";
                                    delete nt;
                                }
                                break;
                            }
                            default:break;
                            }
                            break;
                        }
                        else if (Rec.Event.KeyEvent.uChar.AsciiChar == 'x')
                        {
                            cout << "Cancel buying\n";
                            break;
                        }
                    }
                    else if (Rec.Event.KeyEvent.uChar.AsciiChar == 'x')
                    {
                        cout << "Cancel buying\n";
                        break;
                    }
                }
            }
        }
        if (Rec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN || Rec.Event.KeyEvent.uChar.AsciiChar == 'x')
            break;
    }
}
