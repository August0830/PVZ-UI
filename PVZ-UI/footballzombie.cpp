#include "footballzombie.h"

FootballZombie::FootballZombie()
{
    life = 1670;
    attack = 100 *33/1000;
    speed = 80.0*33/1000/2.5;
    setMovie("://image/FootballZombieWalk.gif");
}

void FootballZombie::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(life<=0)
    {
        if(state<2)
        {
            state=2;
            setMovie("://image/ZombieDie.gif");
            setHead("://image/ZombieHead.gif");
        }
        else if(movie->currentFrameNumber()==movie->frameCount()-1)
            delete this;
        return;
    }
    QList<QGraphicsItem*>items = collidingItems();
    if(!items.empty())
    {
        Plant *plant = qgraphicsitem_cast<Plant*>(items[0]);
        plant->life-=attack;//僵尸发动攻击
        if(state!=1)
        {
            state=1;
            setMovie("://image/FootballZombieAttack.gif");
        }
        return ;
    }
    if(state)
    {
        state=0;
        setMovie("://image/FootballZombieWalk.gif");
    }
    setX(x()-speed);
}
