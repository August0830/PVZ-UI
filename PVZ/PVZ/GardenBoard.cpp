#include <iostream>
#include "GardenBoard.h"
#include <stdio.h>  
#include <windows.h>  
#include <conio.h>  
#include <time.h>
using namespace std;
bool GAME_FAIL = false;//����ȫ�ֱ����Ǳ���ͨ�ţ���ʱ�����л����
extern const int Y_MAX;
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
    
    for (int i = 0; i < row_total; ++i)
    {
        tst.Y = 3 + 7 * i;
        for (auto plant : garden_pos[i])
        {
            if (!plant || ((Plant*)plant)->type != 'p') continue;
            tst.X = 7 + 15 * ((Plant*)plant)->col;
            //tst.Y++;
            SetConsoleCursorPosition(hOutput, tst);
            cout << ((Plant*)plant)->plant_name;
        }
        for (auto zombie : garden_pos[i])
        {
            if (!zombie || ((Zombie*)zombie)->type != 'z') continue;
            tst.X = 7 + 15 * ((Zombie*)zombie)->col;
            //tst.Y--;
            SetConsoleCursorPosition(hOutput, tst);
            cout << "Zombie";// << " " << ((Zombie*)zombie)->col << " " << ((Zombie*)zombie)->life;
        }
    }

    tst.X = 0; tst.Y = 22;
    SetConsoleCursorPosition(hOutput, tst);
    cout << "Total Points: " << point_cnt;
    tst.X = 0; tst.Y = 23;
    SetConsoleCursorPosition(hOutput, tst);
    cout << "Sun Deposit: " << sun_deposit;
    tst.X = 30; tst.Y = 22;
    SetConsoleCursorPosition(hOutput, tst);
    cout << "Shop: ";//
    cout << "a Sunflower b Pea Shooter ";
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
    for (int i = 0; i < 2*row_total&& garden_pos[row_ini][col_total - 1]
        && zombie_cnt[row_ini] >= zombie_max / 2 != NULL; ++i)
        //����һ�м���̫�ཀྵʬ
    {
            row_ini = rand() % row_total;
    }
    if (garden_pos[row_ini][col_total - 1])
        return false;
    else
    {
        //cout << row_ini << endl;
        Zombie* zm = new Zombie(row_ini,7); 
        garden_pos[zm->row][zm->col] = zm;
        zombie_cnt[zm->row]++;
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
        print_garden();
        for (int i = 0; i < row_total; ++i)
        {
            for (int j = 0; j < col_total; ++j)
            {
                if (!garden_pos[i][j]) continue;
                Plant* plt = (Plant*)(garden_pos[i][j]);
                Zombie* zom = (Zombie*)(garden_pos[i][j]);
                if (plt->type == 'p' && plt->plant_name == "Shooter")
                {
                    Shooter* shot = (Shooter*)plt;
                    for (int k = j + 1; k < col_total; ++k)
                    {
                        //�����м�⵽��ʬ�ͷ����ӵ�
                        if (garden_pos[i][k] && ((Zombie*)(garden_pos[i][k]))->type == 'z')
                        {
                            //((Shooter*)plt)->attacking((Zombie*)(garden.garden_pos[i][k]));
                            shot->attacking();
                            for (vector<Bullet*>::iterator it = shot->bullet_set.begin(); it != shot->bullet_set.end();)
                            {
                                if ((*it)->col > Y_MAX)
                                {
                                    it = shot->bullet_set.erase(it);
                                }//����ɳ�������ӵ�
                                else if ((*it)->col- 1 == ((Zombie*)(garden_pos[i][k]))->col
                                    || (*it)->col == ((Zombie*)(garden_pos[i][k]))->col)
                                {
                                    (*it)->attacking((Zombie*)(garden_pos[i][k]));
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
                if (zom->type == 'z')
                {
                    if (garden_pos[zom->row][zom->col - 1])
                    {
                        Plant* plt = (Plant*)(garden_pos[zom->row][zom->col - 1]);
                        if (plt->type == 'p')
                        {
                            plt->get_hurt(zom);
                           // COORD output = { 32,24 };
                            //SetConsoleCursorPosition(hOutput, output);
                            //cout << "Zombie attacked! ";
                        }
                    }
                }
            }
        }//ֲ��ͽ�ʬ���๥�������ڻ�԰�ṩ��λ����Ϣ�����ù����ĺ���

        for (int i = 0; i < row_total; ++i)
        {
            for (int j = 0; j < col_total; ++j)
            {
                if (!garden_pos[i][j]) continue;
                if (((Plant*)garden_pos[i][j])->type == 'p')
                {

                    if (((Plant*)garden_pos[i][j])->life <= 0)
                    {
                        delete garden_pos[i][j];
                        //cout << "Plant died";
                        garden_pos[i][j] = NULL;
                    }//���������ֲ��
                    else if (((Shooter*)garden_pos[i][j])->plant_name == "Shooter")
                        //�ӵ��ĸ���
                    {
                        Shooter* shot = ((Shooter*)garden_pos[i][j]);
                        for (vector<Bullet*>::iterator it = shot->bullet_set.begin(); it != shot->bullet_set.end();)
                        {
                            if ((*it)->col>= Y_MAX)
                            {
                                it = shot->bullet_set.erase(it);
                            }//����Ѿ��ɳ�������ӵ�
                            else
                            {

                                (*it)->move(garden_pos);
                                (*it)->print_bullet(hOutput);
                                it++;
                            }//�Զ��ƶ����Ҵ�ӡ
                        }
                    }
                }
                else if (((Zombie*)garden_pos[i][j])->type == 'z')
                {
                    Zombie* zom = ((Zombie*)garden_pos[i][j]);
                    if (zom->life <= 0)
                    {
                        get_score(10);//֮��������óɲ�ͬ�ķ���ֵ
                        zombie_counting(-1, i);
                        delete garden_pos[i][j];
                        COORD output = { 7+15*(j),3+7*i };
                        if (output.X <= 119)
                        {
                            SetConsoleCursorPosition(hOutput, output);
                            cout << "Zombie died!";
                        }
                        garden_pos[i][j] = NULL;
                    }//��������Ľ�ʬ���ҼƷ�/���½�ʬ�� 
                    else
                    {
                        //COORD output = { 7 + 15 * j,3 + 7 * i+1 };
                        //SetConsoleCursorPosition(hOutput, output);
                        //cout << "life: "<<zom->life;
                        zom->move(garden_pos, i, j);
                    }
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
                vector<char> shop_list{ 'a','b' };
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
                                    garden_pos[row][col] = sunflower;
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
                                    garden_pos[row][col] = shot;
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
