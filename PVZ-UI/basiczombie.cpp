#include "basiczombie.h"

BasicZombie::BasicZombie()
{
    life = 270;
    attack = 100 *33/1000;
    speed = 80.0*33/1000/4.7;
    if(qrand()%2)
        setMovie("://image/ZombieWalk1.gif");
    else
        setMovie("://image/ZombieWalk2.gif");
}

void BasicZombie::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(life<=0)
    {
        if(state<2)//state 0 行走 1 攻击 2 死亡
        {
            state=2;
            setMovie("://image/ZombieDie.gif");
            setHead("://image/ZombieHead.gif");
        }
        else if(movie->currentFrameNumber()==movie->frameCount()-1)
            delete this;
        return;
    }
    QList<QGraphicsItem*> items = collidingItems();
    if(!items.isEmpty())
    {
        Plant *plant = qgraphicsitem_cast<Plant*>(items[0]);
        plant->life-=attack;//僵尸发动攻击
        if(state!=1)
        {
            state=1;
            setMovie("://image/ZombieAttack.gif");
        }
        return ;
    }
    if(state)
    {
        state=0;
        if(qrand()%2)
            setMovie("://image/ZombieWalk1.gif");
        else
            setMovie("://image/ZombieWalk2.gif");
    }
    setX(x()-speed);
}
